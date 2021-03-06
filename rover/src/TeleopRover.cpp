#include <ros/ros.h>
#include <std_msgs/Float64.h>		// for servos
#include <geometry_msgs/Twist.h>	// for drive
#include <sensor_msgs/Joy.h>			// for joystick
#include "TeleopRover.h"

TeleopRover::TeleopRover() {
	m_n.param("axis_linear", m_linear, 1);
	m_n.param("axis_angular", m_angular, 0);
	m_n.param("axis_pan", m_panservo, 2);
	m_n.param("axis_tilt", m_tiltservo, 3);
	m_n.param("button_kinect_up", m_tiltkinect_up, 4);
	m_n.param("button_kinect_down", m_tiltkinect_down, 6);
	m_n.param("button_autonomous_mode_on", m_autonomous_on, 14);
	m_n.param("button_autonomous_mode_off", m_autonomous_off, 15);
	m_n.param("button_enable_cam", m_enable_cam, 11);
	m_n.param("button_enable_move", m_enable_motors, 10);
	m_n.param("speed", m_limit_speed, 0.5);
	m_n.param("angular_speed", m_limit_angular_speed, PI);

	m_cmd_vel_pub = m_n.advertise<geometry_msgs::Twist> ("cmd_vel", 1);
	m_servo_tilt_pub = m_n.advertise<std_msgs::Float64> ("tilt/angle", 1);
	m_servo_pan_pub = m_n.advertise<std_msgs::Float64> ("pan/angle", 1);
	m_kinect_tilt_pub = m_n.advertise<std_msgs::Float64> ("kinect/angle", 1);

	m_joy_sub = m_n.subscribe<sensor_msgs::Joy> ("joy", 10,
			&TeleopRover::joyCallback, this);

	std_msgs::Float64 kinect_msg;
	m_n.param("kinect_default_angle", kinect_msg.data, 0.0);
	m_kinect_angle = kinect_msg.data;
	m_kinect_tilt_pub.publish(kinect_msg);
}

void TeleopRover::joyCallback(const sensor_msgs::Joy::ConstPtr& joy) {
	if (joy->buttons[m_autonomous_on]) {
		m_autoMode = true;
	}

	if (joy->buttons[m_autonomous_off]) {
		m_autoMode = false;
	}

	if (m_autoMode) {
		m_n.setParam("autoMode", 1);
	} else {
		m_n.setParam("autoMode", 0);

		// set kinect
		std_msgs::Float64 kinectServoAngle;

		kinectServoAngle.data = m_kinect_angle;

		if (joy->buttons[m_enable_motors]) {
			// set velocity
			geometry_msgs::Twist cmd_vel;
			cmd_vel.linear.x
					= scale(joy->axes[m_linear], -1.0, 1.0, -m_limit_speed, m_limit_speed);
			cmd_vel.angular.z
					= scale(joy->axes[m_angular], -1.0, 1.0, -m_limit_angular_speed, m_limit_angular_speed);
			m_cmd_vel_pub.publish(cmd_vel);
		} else {
			// stop the robot
			geometry_msgs::Twist cmd_vel;
			cmd_vel.linear.x = 0.0;
			cmd_vel.angular.z = 0.0;
			m_cmd_vel_pub.publish(cmd_vel);
		}

		if (joy->buttons[m_enable_cam]) {
			// set tilt servo
			std_msgs::Float64 tiltServoAngle;
			tiltServoAngle.data
					= scale(expo(joy->axes[m_tiltservo]), -1.0, 1.0, -HALF_PI, HALF_PI);
			m_servo_tilt_pub.publish(tiltServoAngle);

			// set pan servo
			std_msgs::Float64 panServoAngle;
			panServoAngle.data
					= scale(expo(joy->axes[m_panservo]), -1.0, 1.0, -HALF_PI, HALF_PI);
			m_servo_pan_pub.publish(panServoAngle);

			// if (joy->buttons[m_tiltkinect_up]) {
			//     kinectServoAngle.data += 0.001;
			// } else if (joy->buttons[m_tiltkinect_down]) {
			//     kinectServoAngle.data -= 0.001;
			// }

			// kinectServoAngle.data = constrain(kinectServoAngle.data, -KINECT_LIMIT_ANGLE, KINECT_LIMIT_ANGLE);

			// m_kinect_angle = kinectServoAngle.data;

			// m_kinect_tilt_pub.publish(kinectServoAngle);
		}
	}
}
