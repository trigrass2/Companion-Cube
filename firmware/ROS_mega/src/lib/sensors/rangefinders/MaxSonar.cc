/*
 * MaxSonar.cpp
 *
 *  Created on: Nov 20, 2010
 *      Author: rbtying
 */

#include "MaxSonar.h"

MaxSonar::MaxSonar(uint8_t pin) {
	m_pin = pin;
}

double MaxSonar::get_dist() {
	float voltage = analogRead(m_pin) * 5.0 / 1024.0 * 2.54;
	return voltage * 100;
}
