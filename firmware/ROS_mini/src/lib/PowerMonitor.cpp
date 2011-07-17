/*
 * PowerMonitor.cpp
 *
 *  Created on: Apr 11, 2011
 *      Author: rbtying
 */

#include "WProgram.h"
#include "PowerMonitor.h"

PowerMonitor::PowerMonitor() {
	PowerMonitor::PowerMonitor(0, 0);
}

PowerMonitor::PowerMonitor(uint8_t vPin, uint8_t iPin) {
	PowerMonitor::set(vPin, iPin);
}

void PowerMonitor::set(uint8_t vPin, uint8_t iPin) {
	if (vPin != 0 && iPin != 0) {
		m_vPin = vPin;
		m_iPin = iPin;
		pinMode(m_vPin, INPUT);
		pinMode(m_iPin, INPUT);
		digitalWrite(m_vPin, LOW); // turn off pullup
		digitalWrite(m_iPin, LOW); // turn off pullup
	}
}

float PowerMonitor::getVoltage() {
	uint16_t adcRead = analogRead(m_vPin);
	float voltage = adcRead * 0.076660156; // 1v:15.7v voltage divider
	return voltage;
}

float PowerMonitor::getCurrent() {
	uint16_t adcRead = analogRead(m_iPin);
	float current = adcRead * 0.13351995; // 90.15A:3.3v scaling factor
	return current;
}
