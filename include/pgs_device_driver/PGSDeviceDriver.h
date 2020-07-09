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
#include "serial/serial.h"
#include <cstdint>
#include <cmath>

#include "pgs_device_driver/PGSCmd.h"
#include "pgs_device_driver/ethanolsensor.h"

namespace pgs_device_driver {

class PGSDeviceDriver {
public:
	PGSDeviceDriver();
	~PGSDeviceDriver();
	bool command(pgs_device_driver::PGSCmd::Request &req,
			pgs_device_driver::PGSCmd::Response &res);
	std::string findSerialCmd(float scalar);
	void readData(const ros::TimerEvent& event);

private:
	serial::Serial m_serial;
	ros::ServiceServer m_service;
	ros::Publisher m_data_pub;
	ros::Timer m_timer;
};

}




#endif /* PGS_DEVICE_DRIVER_INCLUDE_PGS_DEVICE_DRIVER_PGSDEVICEDRIVER_H_ */
