#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <ros/ros.h>
#include <string>
#include "control_opcodes.h"
#include "cereal_port/CerealPort.h"
#include "util.h"

// dimensions
#define ROVER_DEFAULT_AXLE_LENGTH 0.240164856

#define ROVER_MAX_VEL_MM 500

#define QPPS_TO_M_S 9.78134873e-6

namespace rover {
class interface {
public:

	interface(const char * new_serial_port);
	~interface();

	int openSerialPort();
	int closeSerialPort();

	int getSensorPackets(int timeout);

	int drive(double linear_speed, double angular_speed);
	int driveDirect(int left_speed, int right_speed);

	int setServos(double panAngle, double tiltAngle);
    int setMotorsRaw(int8_t left, int8_t right);

    void setConversionFactors(double left, double right);
	void setPID(double lP, double lI, double lD, double rP, double rI, double rD);
    
    void setLCD(std::string text, int lineNum);

	void resetOdometry();
	void setOdometry(double new_x, double new_y, double new_yaw);

	double m_odometry_x;
	double m_odometry_y;
	double m_odometry_yaw;
	double m_gyro_yaw;
	double m_velocity_x;
	double m_velocity_y;
	double m_velocity_yaw;
	double m_gyro_yawrate;
	double m_gyro_offset;

	double m_battery_voltage;
	double m_battery_current;
    double m_motor_voltage;
    double m_motor_current;
	
    double m_velocity_left, m_velocity_right;
    long m_encoder_left, m_encoder_right;

    int8_t m_left_raw;
    int8_t m_right_raw;

	double m_tilt_angle;
	double m_pan_angle;

	double m_roverAxleLength;
    double m_max_vel;
    double m_gyro_correction;

	bool newPacket;
    bool newLeftEncPacket;
    bool newRightEncPacket;
    bool newEncPacket;
private:
	long m_last_enc_left, m_last_enc_right;
    ros::Time m_lastEncoderUpdateTime;
    ros::Time m_lastYawGyroUpdateTime;
	std::string m_port_name;
	cereal::CerealPort * m_port;
	void calculateOdometry(double dt);
	void processPacket(std::string * packet);
};

}

#endif
