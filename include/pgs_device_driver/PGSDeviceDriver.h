/*
 * PGSDeviceDriver.h
 *
 *  Created on: Jul 9, 2020
 *      Author: morin
 */

#ifndef PGS_DEVICE_DRIVER_INCLUDE_PGS_DEVICE_DRIVER_PGSDEVICEDRIVER_H_
#define PGS_DEVICE_DRIVER_INCLUDE_PGS_DEVICE_DRIVER_PGSDEVICEDRIVER_H_
#include <string>
#include <ros/ros.h>
#include "pgs_device_driver/PGSCmd.h"
#include <serial/serial.h>
#include <cstdint>
#include <cmath>
namespace pgs_device_driver {

class PGSDeviceDriver {
public:
	PGSDeviceDriver();
	~PGSDeviceDriver();
	bool command(pgs_device_driver::PGSCmd::Request &req,
			pgs_device_driver::PGSCmd::Response &res);
	std::string findSerialCmd(float scalar);

private:
	serial::Serial m_serial;
	ros::ServiceServer m_service;
};

}




#endif /* PGS_DEVICE_DRIVER_INCLUDE_PGS_DEVICE_DRIVER_PGSDEVICEDRIVER_H_ */
