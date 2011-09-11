/*
 * Controller.cpp
 *
 *  Created on: Feb 21, 2011
 *      Author: rbtying
 */

#include "OpcodeController.h"
#include "pins.h"

OpcodeController::OpcodeController(control_data * ctrl, HardwareSerial * hws) {
	m_ctrl = ctrl;
	m_hws = hws;

	comm = false;
	m_poll = true;
	m_lastUpdateTime = 0;
}

/**
 * Update the buffer
 */
void OpcodeController::update() {
	if (m_poll && (m_lastPacketSendTime - millis() > CMD_PACKET_INTERVAL)) {
		OpcodeController::sendDataPacket();
	}

	while (m_hws->available()) {
		m_lastUpdateTime = millis();
		char c = m_hws->read();

		byte msg[16];

		switch (c) {
		case CTRL_OP_TOGGLE_POLL:
			m_poll = nextByte(250);
			break;
		case CTRL_OP_SET_DRIVE:
			for (uint8_t i = 0; i < 4; i++) {
				msg[i] = nextByte(250);
			}
			m_ctrl->leftPID.set = ((msg[0] << 8) | msg[1]) * 0.1; // mm/s -> cm/s
			m_ctrl->rightPID.set = ((msg[2] << 8) | msg[3]) * 0.1; // mm/s -> cm/s
			break;
		case CTRL_OP_SET_SERVO:
			msg[0] = nextByte(100);
			msg[1] = nextByte(100);
			msg[0] = constrain(msg[0], 0, 180);
			msg[1] = constrain(msg[1], 0, 180);
			m_ctrl->pan.write(msg[0]);
			m_ctrl->tilt.write(msg[1]);
			break;
		case CTRL_OP_SET_PID:
			for (uint8_t i = 0; i < 12; i++) {
				msg[i] = nextByte(250);
			}
			m_ctrl->leftPID.proportional = ((msg[0] << 8) | msg[1]) * 0.01;
			m_ctrl->leftPID.integral = ((msg[2] << 8) | msg[3]) * 0.01;
			m_ctrl->leftPID.derivative = ((msg[4] << 8) | msg[5]) * 0.01;

			m_ctrl->rightPID.proportional = ((msg[6] << 8) | msg[7]) * 0.01;
			m_ctrl->rightPID.integral = ((msg[8] << 8) | msg[9]) * 0.01;
			m_ctrl->rightPID.derivative = ((msg[10] << 8) | msg[11]) * 0.01;
			break;
		case CTRL_OP_SET_CONV:
			for (uint8_t i = 0; i < 4; i++) {
				msg[i] = nextByte(250);
			}
			m_ctrl->leftEnc.cmPerCount = ((msg[0] << 8) | msg[1]) * 0.0001;
			m_ctrl->rightEnc.cmPerCount = ((msg[2] << 8) | msg[3]) * 0.0001;
			break;
		case CTRL_OP_SET_MOTOR:
			msg[0] = nextByte(250);
			msg[1] = nextByte(250);
			m_ctrl->mot.leftSpeed = (int8_t) msg[0];
			m_ctrl->mot.rightSpeed = (int8_t) msg[1];
			break;
		case CTRL_OP_SET_LCD:
			char lcd_msg[LCD_COLS + 1];
			msg[0] = nextByte(250);
			for (uint8_t i = 0; i < LCD_COLS; i++) {
				lcd_msg[i] = nextByte(250);
			}
			lcd_msg[LCD_COLS] = '\0';
			m_ctrl->lcd->setCursor(0, constrain(msg[0], 0, LCD_LINES));
			m_ctrl->lcd->print(lcd_msg);
			break;
		case CTRL_OP_GET_BATTERY_HUMAN:
			m_hws->print("BAT0: ");
			m_hws->print(m_ctrl->cpu_batt.getVoltage(), DEC);
			m_hws->print(" volts, ");
			m_hws->print(m_ctrl->cpu_batt.getCurrent(), DEC);
			m_hws->print(" amps\r\n");
			m_hws->print("BAT1: ");
			m_hws->print(m_ctrl->mot_batt.getVoltage(), DEC);
			m_hws->print(" volts, ");
			m_hws->print(m_ctrl->mot_batt.getCurrent(), DEC);
			m_hws->print(" amps\r\n");
			break;
		default:
			m_hws->print("Invalid opcode");
		}
	}
	comm = (millis() - m_lastUpdateTime) <= CMD_TIMEOUT;
}

void OpcodeController::sendMessage(uint8_t op, uint8_t * contents,
		uint8_t length) {
	uint8_t msg[length + 4]; // checksum byte + op + leading + ending
	msg[0] = '<';
	msg[1] = op;
	for (uint8_t i = 0; i < length; i++) {
		if (contents[i] != '<' && contents[i] != '>') {
			msg[2 + i] = contents[i];
		} else {
			msg[2 + i] = '=';
			contents[i] = '=';
		}
	}
	uint8_t chk = checksum(op, contents, length);
	msg[length + 2] = (chk == '>' || chk == '<') ? '=' : chk;
	msg[length + 3] = '>';
	m_hws->write(msg, length + 4);
}

uint8_t OpcodeController::checksum(uint8_t op, uint8_t * contents,
		uint8_t length) {
	uint32_t temp = op;
	for (uint8_t i = 0; i < length; i++) {
		temp += contents[i];
	}
	return temp & 0b01111111;
}

void OpcodeController::sendEncoderMessage(uint8_t op, encoder_data * d,
		uint8_t out) {
	uint8_t buf[7];

	int16_t speed = d->velocity * 100;
	int32_t count = d->count;

	buf[0] = speed >> 8u;
	buf[1] = speed & 0xff;
	buf[2] = count >> 24u;
	buf[3] = count >> 16u;
	buf[4] = count >> 8u;
	buf[5] = count & 0xff;
	buf[6] = out & 0xff;

	sendMessage(op, buf, 7);
}

void OpcodeController::sendEncodersMessage(uint8_t op, encoder_data * d1,
		encoder_data * d2, uint8_t out1, uint8_t out2) {
	uint8_t buf[14];
	int16_t speed1 = d1->velocity * 100;
	int32_t count1 = d1->count;
	int16_t speed2 = d2->velocity * 100;
	int32_t count2 = d2->count;

	buf[0] = speed1 >> 8u;
	buf[1] = speed1 & 0xff;
	buf[2] = count1 >> 24u;
	buf[3] = count1 >> 16u;
	buf[4] = count1 >> 8u;
	buf[5] = count1 & 0xff;
	buf[6] = out1 & 0xff;
	buf[7] = speed2 >> 8u;
	buf[8] = speed2 & 0xff;
	buf[9] = count2 >> 24u;
	buf[10] = count2 >> 16u;
	buf[11] = count2 >> 8u;
	buf[12] = count2 & 0xff;
	buf[13] = out2 & 0xff;

	sendMessage(op, buf, 14);
}

void OpcodeController::sendGyroMessage(uint8_t op, gyro_data * d) {
	uint8_t buf[4];

	int16_t rate = d->rate * 1000;
	int16_t val = d->val * 1000;

	buf[0] = rate >> 8u;
	buf[1] = rate & 0xff;
	buf[2] = val >> 8u;
	buf[3] = val & 0xff;

	sendMessage(op, buf, 4);
}

void OpcodeController::sendBatteryMessage(uint8_t op, Battery * b) {
	uint8_t buf[4];

	int16_t v = b->getVoltage() * 100;
	int16_t i = b->getCurrent() * 100;

	buf[0] = v >> 8u;
	buf[1] = v & 0xff;
	buf[2] = i >> 8u;
	buf[3] = i & 0xff;

	sendMessage(op, buf, 4);
}

void OpcodeController::sendServoMessage(uint8_t op, uint8_t angle) {
	uint8_t buf[1];
	buf[0] = angle;
	sendMessage(op, buf, 1);
}

void OpcodeController::sendServosMessage(uint8_t op, uint8_t angle1,
		uint8_t angle2) {
	uint8_t buf[2];
	buf[0] = angle1;
	buf[1] = angle2;
	sendMessage(op, buf, 2);
}

/**
 * Send a full data packet
 */
void OpcodeController::sendDataPacket() {
	//	sendEncoderMessage(MSG_OP_LEFT_ENC, &(m_ctrl->leftEnc),
	//			(uint8_t) (m_ctrl->mot.leftSpeed & 0xff));
	//	sendEncoderMessage(MSG_OP_RIGHT_ENC, &(m_ctrl->rightEnc),
	//			(uint8_t) (m_ctrl->mot.rightSpeed & 0xff));
	sendEncodersMessage(MSG_OP_BOTH_ENC, &(m_ctrl->leftEnc),
			&(m_ctrl->rightEnc), (uint8_t) (m_ctrl->mot.leftSpeed & 0xff),
			(uint8_t) (m_ctrl->mot.rightSpeed & 0xff));
	sendGyroMessage(MSG_OP_YAW_GYRO, &(m_ctrl->yaw));
	sendBatteryMessage(MSG_OP_CPU_BAT, &(m_ctrl->cpu_batt));
	sendBatteryMessage(MSG_OP_MOTOR_BAT, &(m_ctrl->mot_batt));
	sendServosMessage(MSG_OP_BOTH_SERVO, m_ctrl->pan.read(),
			m_ctrl->tilt.read());
	//	sendServoMessage(MSG_OP_PAN_SERVO, m_ctrl->pan.read());
	//	sendServoMessage(MSG_OP_TILT_SERVO, m_ctrl->tilt.read());
}

/**
 * Request a byte from Serial
 */
char OpcodeController::nextByte(unsigned long timeout) {
	unsigned long timeOutTime = millis() + timeout;
	while (millis() < timeOutTime && !m_hws->available()) {
		// do nothing
	}
	if (m_hws->available())
		return m_hws->read();
	else
		return 0x00;
}
