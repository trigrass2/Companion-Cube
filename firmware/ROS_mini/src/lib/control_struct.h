/*
 * control_struct.h
 *
 *  Created on: Jul 17, 2011
 *      Author: rbtying
 */

#ifndef CONTROL_STRUCT_H_
#define CONTROL_STRUCT_H_

#include "libraries/Servo/Servo.h"
#include "PowerMonitor.h"

struct PID_params {
	double set;
	double input;
	double output;
	double accumulated;
	double previous;
	double error;

	double proportional;
	double integral;
	double derivative;

	double accLimit;
};

typedef struct PID_params PID_params;

struct gyro_data {
	double rate;
	double val;
};

typedef struct gyro_data gyro_data;

struct encoder_data {
	volatile long count;
	volatile long pCount;

	volatile unsigned long time;
	volatile unsigned long pTime;

	volatile bool dir;
	volatile double velocity;

	double cmPerCount;
};

typedef struct encoder_data encoder_data;

struct motor_data {
	int16_t leftSpeed;
	int16_t rightSpeed;
};

typedef struct motor_data motor_data;

struct control_data {
	PowerMonitor cpu_batt;
	PowerMonitor mot_batt;
	gyro_data yaw;
	Servo pan;
	Servo tilt;
	PID_params leftPID;
	PID_params rightPID;
	encoder_data leftEnc;
	encoder_data rightEnc;
	motor_data mot;
};

typedef struct control_data control_data;

#endif /* CONTROL_STRUCT_H_ */
