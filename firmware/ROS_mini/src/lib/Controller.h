/*
 * Controller.h
 *
 *  Created on: Feb 21, 2011
 *      Author: rbtying
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "WProgram.h"
#include "PowerMonitor.h"
#include "control_struct.h"
#include "libraries/Servo/Servo.h"

#define CMD_BUFFER_SIZE 8
#define CMD_PACKET_SIZE 17
#define CMD_PACKET_INTERVAL 100 // 10 Hz
#define CMD_STARTCHAR ':'
#define CMD_ENDCHAR '!'
#define CMD_TIMEOUT 1000

class Controller {

public:
	Controller(control_data * ctrl);
	void update();
	void printInfo();

	bool comm;

private:
	control_data * m_ctrl;

	unsigned long m_lastUpdateTime, m_lastPacketSendTime;
	char m_buf[CMD_BUFFER_SIZE];
	uint8_t m_dataPacket[CMD_PACKET_SIZE];
	uint8_t m_bufPtr;
	void processCommand();
	void sendDataPacket();
	char nextByte(unsigned long timeout);
	void flush();
};

#endif /* CONTROLLER_H_ */
