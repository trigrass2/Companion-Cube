/*
 * state_struct.h
 *
 *  Created on: Dec 1, 2011
 *      Author: rbtying
 */

#ifndef STATE_STRUCT_H_
#define STATE_STRUCT_H_

struct robot_state {
	uint8_t servo_pan_val; // pan servo angle, degrees
	uint8_t servo_tilt_val; // tilt servo angle, degrees
	int16_t batt_motor_voltage; // battery voltage * 100
	int16_t batt_motor_current; // battery current * 100
	int16_t gyro_yaw_rate; // gyro rate * 1000
	int16_t gyro_yaw_val; // gyro val * 1000
	int16_t enc_left_speed; // velocity (cm/s) * 100
	int16_t enc_right_speed; // velocity (cm/s) * 100
	int32_t enc_left_count; // count
	int32_t enc_right_count; // count
	int16_t enc_left_conv; // cmpercount * 1000
	int16_t enc_right_conv; // cmpercount * 1000
	int8_t motor_left_val; // value
	int8_t motor_right_val; // value
	int16_t pid_left_proportional; // * 100
	int16_t pid_left_integral; // * 100
	int16_t pid_left_derivative; // * 100
	int16_t pid_left_setpoint; // cm/s * 10
	int16_t pid_right_proportional; // * 100
	int16_t pid_right_integral; // * 100
	int16_t pid_right_derivative; // * 100
	int16_t pid_right_setpoint; // cm/s * 10
};
typedef struct robot_state robot_state;

#define STATE_STRUCT_SIZE 44

inline void byteToStateStruct(uint8_t * buf, robot_state * state) {
	state->servo_pan_val = buf[0];
	state->servo_tilt_val = buf[1];
	state->batt_motor_voltage = buf[2] << 8u | buf[3];
	state->batt_motor_current = buf[4] << 8u | buf[5];
	state->gyro_yaw_rate = buf[6] << 8u | buf[7];
	state->gyro_yaw_val = buf[8] << 8u | buf[9];
	state->enc_left_speed = buf[10] << 8u | buf[11];
	state->enc_right_speed = buf[12] << 8u | buf[13];
	state->enc_left_count = ((uint32_t) buf[14]) << 24u | ((uint32_t) buf[15])
			<< 16u | ((uint16_t) buf[16]) << 8u | buf[17];
	state->enc_right_count = ((uint32_t) buf[18]) << 24u | ((uint32_t) buf[19])
			<< 16u | ((uint16_t) buf[20]) << 8u | buf[21];
	state->enc_left_conv = buf[22] << 8u | buf[23];
	state->enc_right_conv = buf[24] << 8u | buf[25];
	state->motor_left_val = buf[26];
	state->motor_right_val = buf[27];
	state->pid_left_proportional = buf[28] << 8u | buf[29];
	state->pid_left_integral = buf[30] << 8u | buf[31];
	state->pid_left_derivative = buf[32] << 8u | buf[33];
	state->pid_left_setpoint = buf[34] << 8u | buf[35];
	state->pid_right_proportional = buf[36] << 8u | buf[37];
	state->pid_right_integral = buf[38] << 8u | buf[39];
	state->pid_right_derivative = buf[40] << 8u | buf[41];
	state->pid_right_setpoint = buf[42] << 8u | buf[43];
}

inline void stateStructToByte(robot_state * state, uint8_t * buf) {
	buf[0] = state->servo_pan_val;
	buf[1] = state->servo_tilt_val;
	buf[2] = state->batt_motor_voltage >> 8u;
	buf[3] = state->batt_motor_voltage & 0xff;
	buf[4] = state->batt_motor_current >> 8u;
	buf[5] = state->batt_motor_current & 0xff;
	buf[6] = state->gyro_yaw_rate >> 8u;
	buf[7] = state->gyro_yaw_rate & 0xff;
	buf[8] = state->gyro_yaw_val >> 8u;
	buf[9] = state->gyro_yaw_val & 0xff;
	buf[10] = state->enc_left_speed >> 8u;
	buf[11] = state->enc_left_speed & 0xff;
	buf[12] = state->enc_right_speed >> 8u;
	buf[13] = state->enc_right_speed & 0xff;
	buf[14] = state->enc_left_count >> 24u;
	buf[15] = state->enc_left_count >> 16u;
	buf[16] = state->enc_left_count >> 8u;
	buf[17] = state->enc_left_count & 0xff;
	buf[18] = state->enc_right_count >> 24u;
	buf[19] = state->enc_right_count >> 16u;
	buf[20] = state->enc_right_count >> 8u;
	buf[21] = state->enc_right_count & 0xff;
	buf[22] = state->enc_left_conv >> 8u;
	buf[23] = state->enc_left_conv & 0xff;
	buf[24] = state->enc_right_conv >> 8u;
	buf[25] = state->enc_right_conv & 0xff;
	buf[26] = state->motor_left_val;
	buf[27] = state->motor_right_val;
	buf[28] = state->pid_left_proportional >> 8u;
	buf[29] = state->pid_left_proportional & 0xff;
	buf[30] = state->pid_left_integral >> 8u;
	buf[31] = state->pid_left_integral & 0xff;
	buf[32] = state->pid_left_derivative >> 8u;
	buf[33] = state->pid_left_derivative & 0xff;
	buf[34] = state->pid_left_setpoint >> 8u;
	buf[35] = state->pid_left_setpoint & 0xff;
	buf[36] = state->pid_right_proportional >> 8u;
	buf[37] = state->pid_right_proportional & 0xff;
	buf[38] = state->pid_right_integral >> 8u;
	buf[39] = state->pid_right_integral & 0xff;
	buf[40] = state->pid_right_derivative >> 8u;
	buf[41] = state->pid_right_derivative & 0xff;
	buf[42] = state->pid_right_setpoint >> 8u;
	buf[43] = state->pid_right_setpoint & 0xff;
}

#endif /* STATE_STRUCT_H_ */
