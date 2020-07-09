/*
 * pgs_device_driver_node.cpp
 *
 *  Created on: Jul 9, 2020
 *      Author: morin
 */
#include "pgs_device_driver/PGSDeviceDriver.h"
using namespace pgs_device_driver;

int main(int argc, char** argv){
	ros::init(argc, argv, "pgs_device_driver");
	PGSDeviceDriver pgs_device_driver;
	ros::spin();
}

