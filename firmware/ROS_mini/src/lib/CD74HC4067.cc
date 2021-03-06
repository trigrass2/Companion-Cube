/*
 * CD74HC4067.cc
 *
 *  Created on: Apr 28, 2011
 *      Author: rbtying
 */

#include "CD74HC4067.h"
#include "fastIO.h"

/**
 * Constructs the CD74HC4067 analog-digital mux wrapper
 */
CD74HC4067::CD74HC4067(uint8_t mux1, uint8_t mux2, uint8_t mux3, uint8_t mux4,
		uint8_t mux_adc) {
	m_pins[0] = mux1;
	m_pins[1] = mux2;
	m_pins[2] = mux3;
	m_pins[3] = mux4;
	m_adc = mux_adc;
	for (uint8_t i = 0; i < 4; i++) {
		pinModeFast(m_pins[i], OUTPUT);
	}

	pinModeFast(m_adc, INPUT);
	digitalWriteFast(m_adc, LOW);

	setMux(0); // set to go to pin 0
}

/**
 * Sets up the mux for a read
 */
void CD74HC4067::setMux(uint8_t num) {
	num = constrain(num, 0, 15);

	// if the mux isn't already set to the correct pin
	if (num != m_pnum) {
		// set the mux to the correct pin
		for (uint8_t i = 0; i < 4; i++) {
			digitalWriteFast(m_pins[i], (((num >> i) & 0x01) ? (HIGH) : (LOW)));
		}
	}
	m_pnum = num;
}
/**
 * Reads a single analog value from the mux
 */
uint16_t CD74HC4067::readADC(uint8_t num) {
	setMux(num);
	return (uint16_t) analogRead(m_adc);
}

/**
 * Reads a single digital value from the mux
 */
bool CD74HC4067::readDigital(uint8_t num) {
	setMux(num);
	return (digitalReadFast(m_adc));
}
