/*
 * pins.h
 *
 *  Created on: Dec 8, 2010
 *      Author: rbtying
 */

#ifndef PINS_H_
#define PINS_H_

//  Arduino Pro Mini
//  	      ______
//	 S-TX:D1 |oooooo| Vin
// 	 S-RX:D0 |      | GND
//	     RST |      | RST
//       GND |      | Vcc
// 	LENCA:D2 | A4:o | A3:LED
// 	RENCA:D3 | A5:o | A2:NC
// 	LENCB:D4 |      | A1:NC
//  RENCB:D5 |      | A0:ADCMUX
//   RMOT:D6 |      | D13:MUX4
//   LMOT:D7 |      | D12:MUX3
//    PAN:D8 |      | D11:MUX2
//   TILT:D9 |______| D10:MUX1

// cable:
// 0: GND (red)
// 1: Vcc
// 2: 10: MUX1
// 3: 11: MUX2
// 4: 12: MUX3
// 5: 13: MUX4
// 6: 14: ADC0
// 7:  8: PAN
// 8:  9: TILT
// 9: A3: LED

// ======= START ENCODERS =======
// encoder pins
#define LENC_A 2
#define LENC_B 4
#define RENC_A 3
#define RENC_B 5
// encoder interrupts
#define LENC_INT 0
#define RENC_INT 1
// ======= END ENCODERS =========

// ======= START MOTORS =========
#define SBT_ADDRESS 128
#define SBT_PIN1 7
#define SBT_PIN2 6
// ======= END MOTORS ===========

// ======= START SERVOS =========
#define PANSERVO 8
#define TILTSERVO 9
// ======= END SERVOS ===========

// ======= START MUX ============
#define MUX_1 10
#define MUX_2 11
#define MUX_3 12
#define MUX_4 13
#define MUX_ADC 0
// ======= END MUX ==============

// ======= START BATT ===========
#define VOLTAGE_SENS 13
#define CURRENT_SENS 12
#define MOTOR_VOLTAGE_SENS 11
#define MOTOR_CURRENT_SENS 10
// ======= END BATT =============

// ======= START GYRO ===========
#define YAW_GYRO 14
#define YAW_REF 15
// ======= END GYRO =============

// ======= START LED ============
#define LED 17
// ======= END LED ==============

#endif /* PINS_H_ */
