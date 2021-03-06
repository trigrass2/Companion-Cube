/*
 * DualMotor.h
 *
 *  Created on: Sep 5, 2011
 *      Author: rbtying
 */

#ifndef DUALMOTOR_H_
#define DUALMOTOR_H_

#include <Arduino.h>

struct motor_data {
	int16_t leftSpeed;
	int16_t rightSpeed;
	bool leftFwd;
	bool rightFwd;
};

typedef struct motor_data motor_data;

class DualMotor {
public:
	virtual void setSpeed(motor_data * m) = 0;
};

#endif /* DUALMOTOR_H_ */
