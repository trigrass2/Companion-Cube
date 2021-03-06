/*
 * Sharp_IR.cpp
 *
 *  Created on: Nov 20, 2010
 *      Author: rbtying
 */

#include "Sharp_IR.h"

Sharp_IR::Sharp_IR(uint8_t pin, uint8_t type) {
	m_pin = pin;
	pinMode(m_pin, INPUT);
	m_type = type;
}

float Sharp_IR::get_dist() {
	int value = 0;
	value = analogRead(m_pin);
	switch (m_type) {
	case SR: //short range, aka GP2D120 (4-30cm)
		return (2914 / (value + 5)) - 1;
		break;
	case MR: //medium range, aka GP2D12 (10-80cm)
		return 5 * 2769 / 2 / value/** pow(value, -.9988)*/; //I had to multiply by 5, different sensor
		break;
	case LR: //long range, aka GP2Y0A02YK (20-150cm)
		return 14251 * pow(value, -1.17);
		break;
	}
	return 0;
}
