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
};

typedef struct PID_params PID_params;

struct gyro_data {
	double rate;
	double val;
};

typedef struct gyro_data gyro_data;

struct conversion_data {
	double cmPerCountLeft;
	double cmPerCountRight;
};

typedef struct conversion_data conversion_data;

struct control_data {
	PowerMonitor batt;
	gyro_data yaw;
	Servo pan;
	Servo tilt;
	PID_params leftPID;
	PID_params rightPID;
	conversion_data conv;
};

typedef struct control_data control_data;

#endif /* CONTROL_STRUCT_H_ */
