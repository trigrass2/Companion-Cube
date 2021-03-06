/*
 * Ping.h
 *
 *  Created on: Feb 12, 2011
 *      Author: rbtying
 */

#ifndef PING_H_
#define PING_H_
#include <Arduino.h>
#include "Rangefinder.h"

class Ping: Rangefinder {
public:
	Ping(uint8_t pin);
	double get_dist();

private:
	uint8_t m_pin;
};

#endif /* PING_H_ */
