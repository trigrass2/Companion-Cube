#include <ros/ros.h>
#include "wrapper.h"

int main(int argc, char** argv) {
	ros::init(argc, argv, "rover_node");
	Wrapper rover;
	ros::spin();
}
