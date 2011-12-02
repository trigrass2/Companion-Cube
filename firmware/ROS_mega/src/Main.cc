/*
 * Main.cpp
 *
 *  Created on: September 4th, 2011
 *      Author: rbtying
 */
#include <WProgram.h>
#include "pins.h"
#include "StateController.h"
#include "control_struct.h"
#include "sensors/Gyro.h"
#include "sensors/Battery.h"
#include "utilities/fastIO.h"
#include "utilities/PID.h"
#include "motors/Sabertooth.h"
#include "devices/CD74HC4067.h"
#include "libraries/Servo/Servo.h"

// Control
#define TIME_INTERVAL 100 // 10 Hz
#define LED_INTERVAL 500

unsigned long nexTime = 0, cTime = 0, ledTime = 0;

// control data
control_data ctrl;

#define QP_TO_CM_LEFT (0.004)
#define QP_TO_CM_RIGHT (0.004)

// PID
PID leftPID(&ctrl.leftPID);
PID rightPID(&ctrl.rightPID);

// Yaw Gyroscope
Gyro yawGyro(YAW_GYRO, YAW_REF, LPR510_CONVERSION_FACTOR);

// Motors
Sabertooth m(SBT_ADDRESS, &Serial3);

// Controller
StateController cmd(&ctrl, &Serial);

/**
 * Encoder handlers
 */
void lEncHandler() {
#ifndef LENCREV
	ctrl.leftEnc.dir = !fastIORead(LENC_B);
#else
	ctrl.leftEnc.dir = fastIORead(LENC_B);
#endif
	Encoder::count(&ctrl.leftEnc);
}

void rEncHandler() {
#ifndef RENCREV
	ctrl.rightEnc.dir = !fastIORead(RENC_B);
#else
	ctrl.rightEnc.dir = fastIORead(RENC_B);
#endif
	Encoder::count(&ctrl.rightEnc);
}

/**
 * Main execution loop
 */
int main() {
	init();

	Serial.begin(115200);

	// battery
	ctrl.mot_batt.set(NULL, MOTOR_VOLTAGE_SENS, MOTOR_CURRENT_SENS);

	// servos
	ctrl.pan.write(90);
	ctrl.pan.attach(PANSERVO);
	ctrl.tilt.write(90);
	ctrl.tilt.attach(TILTSERVO);

	// PID
	ctrl.leftPID.proportional = 0.6;
	ctrl.leftPID.integral = 0.1;
	ctrl.leftPID.derivative = 0;
	ctrl.leftPID.accLimit = 127;

	ctrl.rightPID.proportional = 0.6;
	ctrl.rightPID.integral = 0.1;
	ctrl.rightPID.derivative = 0;
	ctrl.rightPID.accLimit = 127;

	ctrl.leftEnc.cmPerCount = QP_TO_CM_LEFT;
	ctrl.rightEnc.cmPerCount = QP_TO_CM_RIGHT;

	// Motors
	ctrl.mot.leftFwd = false;
	ctrl.mot.rightFwd = false;

	// setup encoders
	uint8_t enc_pins[4] = { RENC_A, RENC_B, LENC_A, LENC_B };
	for (uint8_t i = 0; i < 4; i++) {
		fastIOMode(enc_pins[i], INPUT);
		fastIOWrite(enc_pins[i], LOW);
	}
	attachInterrupt(LENC_INT, lEncHandler, RISING);
	attachInterrupt(RENC_INT, rEncHandler, RISING);

	yawGyro.calibrate(1000);

	for (uint32_t loops = 0;; loops++) {
		cTime = millis();
		cmd.update();

		if (nexTime <= cTime) {
			float dt = (TIME_INTERVAL + (cTime - nexTime)) * 0.001;

			// update gyro
			yawGyro.update(&ctrl.yaw, dt);

			// correct for zero drift
			if (abs(ctrl.yaw.rate) <= 0.001 && ctrl.leftEnc.velocity == 0
					&& ctrl.rightEnc.velocity == 0) {// bot is not moving
				yawGyro.calibrate(1000, true); // update calibration
			}

			// Encoder processing
			Encoder::update(&ctrl.leftEnc, dt);
			Encoder::update(&ctrl.rightEnc, dt);

			leftPID.setInput(ctrl.leftEnc.velocity);
			rightPID.setInput(ctrl.rightEnc.velocity);

			leftPID.process(dt);
			rightPID.process(dt);

			ctrl.mot.leftSpeed += leftPID.getOutput();
			ctrl.mot.rightSpeed += rightPID.getOutput();

			ctrl.mot.leftSpeed = constrain(ctrl.mot.leftSpeed, -127, 127);
			ctrl.mot.rightSpeed = constrain(ctrl.mot.rightSpeed, -127, 127);

			m.setSpeed(&ctrl.mot);

			nexTime = cTime + TIME_INTERVAL;
		}
	}
}
