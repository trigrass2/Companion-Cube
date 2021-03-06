/*
 * Gyro.h
 *
 *  Created on: Apr 18, 2011
 *      Author: rbtying
 */

#include <WProgram.h>
#include "CD74HC4067.h"

#ifndef GYRO_H_
#define GYRO_H_

#define LPR510_CONVERSION_FACTOR (0.034088462)
#define NUM_CAL 100

class Gyro {
public:
	Gyro(uint8_t axisPin, uint8_t refPin, float conversion_factor);
	Gyro(CD74HC4067 *mux, uint8_t axisPin, uint8_t refPin,
			float conversion_factor);
	void calibrate(uint16_t num = NUM_CAL, bool continuous = false);
	float getValue();
private:
	CD74HC4067 *m_mux;
	bool m_usingMux;
	uint8_t m_axisPin, m_refPin;
	float m_offset;
	float m_conversion_factor;
};

#endif /* GYRO_H_ */
