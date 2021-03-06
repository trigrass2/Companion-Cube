/*
 * Main.cpp
 *
 *  Created on: Nov 20, 2010
 *      Author: rbtying
 */
#include "WProgram.h"
#include "pins.h"
#include "lib/control_struct.h"
#include "lib/Controller.h"
#include "lib/PowerMonitor.h"
#include "lib/Gyro.h"
#include "lib/fastIO.h"
#include "lib/CD74HC4067.h"
#include "libraries/Servo/Servo.h"

// Control
#define TIME_INTERVAL 100 // 10 Hz
#define LED_INTERVAL 500

unsigned long nexTime = 0, cTime = 0, ledTime = 0;

// control data
control_data ctrl;

#define QP_TO_CM_LEFT (0.004)
#define QP_TO_CM_RIGHT (0.004)

// adc mux:
CD74HC4067 mux(MUX_1, MUX_2, MUX_3, MUX_4, MUX_ADC);

// Yaw Gyroscope
Gyro yawGyro(&mux, YAW_GYRO, YAW_REF, LPR510_CONVERSION_FACTOR);
double yawVal = 0, yawRate = 0;

// Motors
Servo lMot, rMot;

Controller cmd(&ctrl);

/**
 * Sets speeds, +1000 to -1000
 */
void setSpeeds(int8_t left, int8_t right) {
	lMot.writeMicroseconds(map(constrain(left, -127, 127), -127, 127, 2000,
			1000));
	rMot.writeMicroseconds(map(constrain(right, -127, 127), -127, 127, 1000,
			2000));
}

/**
 * Encoder handlers
 */
void lEncHandler() {
#ifndef LENCREV
	ctrl.leftEnc.dir = !digitalReadFast(LENC_B);
#else
	ctrl.leftEnc.dir = digitalReadFast(LENC_B);
#endif
	ctrl.leftEnc.count += ctrl.leftEnc.dir ? +1 : -1;
	ctrl.leftEnc.pTime = ctrl.leftEnc.time;
	ctrl.leftEnc.time = micros();
}

void rEncHandler() {
#ifndef RENCREV
	ctrl.rightEnc.dir = !digitalReadFast(RENC_B);
#else
	ctrl.rightEnc.dir = digitalReadFast(RENC_B);
#endif
	ctrl.rightEnc.count += ctrl.rightEnc.dir ? +1 : -1;
	ctrl.rightEnc.pTime = ctrl.rightEnc.time;
	ctrl.rightEnc.time = micros();
}

void processPID(PID_params * p, float dt) {
	p->error = p->set - p->input;
	p->accumulated += p->error * dt;
	p->accumulated = constrain(p->accumulated, -(p->accLimit), p->accLimit);
	p->output = p->proportional * p->error + p->integral * p->accumulated
			+ p->derivative * (p->error - p->previous) / dt;
	p->previous = p->error;
}

/**
 * Main execution loop
 */
int main() {
	init();

	Serial.begin(115200);

	// battery
	ctrl.cpu_batt.set(&mux, VOLTAGE_SENS, CURRENT_SENS);
	ctrl.mot_batt.set(&mux, MOTOR_VOLTAGE_SENS, MOTOR_CURRENT_SENS);

	// servos
	ctrl.pan.write(90);
	ctrl.pan.attach(PANSERVO);
	ctrl.tilt.write(90);
	ctrl.tilt.attach(TILTSERVO);

	// motors
	setSpeeds(0, 0);
	lMot.attach(SBT_PIN1);
	rMot.attach(SBT_PIN2);

	// PID
	ctrl.leftPID.proportional = 0.3;
	ctrl.leftPID.integral = 0.05;
	ctrl.leftPID.derivative = 0;
	ctrl.leftPID.accLimit = 127;

	ctrl.rightPID.proportional = 0.3;
	ctrl.rightPID.integral = 0.05;
	ctrl.rightPID.derivative = 0;
	ctrl.rightPID.accLimit = 127;

	ctrl.leftEnc.cmPerCount = QP_TO_CM_LEFT;
	ctrl.rightEnc.cmPerCount = QP_TO_CM_RIGHT;

	// setup encoders
	uint8_t enc_pins[4] = { RENC_A, RENC_B, LENC_A, LENC_B };
	for (uint8_t i = 0; i < 4; i++) {
		pinModeFast(enc_pins[i], INPUT);
		digitalWriteFast(enc_pins[i], LOW);
	}
	attachInterrupt(LENC_INT, lEncHandler, RISING);
	attachInterrupt(RENC_INT, rEncHandler, RISING);

	pinMode(LED, OUTPUT);
	digitalWrite(LED, HIGH);

	yawGyro.calibrate(1000);

	for (uint32_t loops = 0;; loops++) {
		cmd.update();

		cTime = millis();

		if (ledTime <= cTime) {
			if (cmd.comm) {
				digitalWriteFast(LED, !digitalReadFast(LED));
			} else {
				digitalWriteFast(LED, LOW);
			}
			ledTime = cTime + LED_INTERVAL;
		}

		if (nexTime <= cTime) {
			float dt = (TIME_INTERVAL + (cTime - nexTime)) * 0.001;

			// update gyro
			ctrl.yaw.rate = yawGyro.getValue();
			ctrl.yaw.val += yawRate * dt;

			// correct for zero drift
			if (abs(ctrl.yaw.rate) <= 0.001 && ctrl.leftPID.set == 0
					&& ctrl.rightPID.set == 0) {// bot is not moving
				yawGyro.calibrate(1000, true); // update calibration
			}

			//			 Encoder processing
			ctrl.leftEnc.velocity = (ctrl.leftEnc.count - ctrl.leftEnc.pCount)
					* ctrl.leftEnc.cmPerCount / dt;
			ctrl.rightEnc.velocity = (ctrl.rightEnc.count
					- ctrl.rightEnc.pCount) * ctrl.rightEnc.cmPerCount / dt;

			ctrl.leftEnc.pCount = ctrl.leftEnc.count;
			ctrl.rightEnc.pCount = ctrl.rightEnc.count;

			ctrl.leftPID.input = ctrl.leftEnc.velocity;
			ctrl.rightPID.input = ctrl.rightEnc.velocity;

			processPID(&ctrl.leftPID, dt);
			processPID(&ctrl.rightPID, dt);

			ctrl.mot.leftSpeed += ctrl.leftPID.output;
			ctrl.mot.rightSpeed += ctrl.rightPID.output;

			ctrl.mot.leftSpeed = constrain(ctrl.mot.leftSpeed, -127, 127);
			ctrl.mot.rightSpeed = constrain(ctrl.mot.rightSpeed, -127, 127);

			setSpeeds(ctrl.mot.leftSpeed & 0xff, ctrl.mot.rightSpeed & 0xff);

			nexTime = cTime + TIME_INTERVAL;
		}
	}
}
