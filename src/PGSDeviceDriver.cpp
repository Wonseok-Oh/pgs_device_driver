/*
 * PGSDeviceDriver.cpp
 *
 *  Created on: Jul 9, 2020
 *      Author: morin
 */

#include "pgs_device_driver/PGSDeviceDriver.h"

using namespace pgs_device_driver;
using namespace std;

PGSDeviceDriver::PGSDeviceDriver(){
	ros::NodeHandle nh;
	ros::NodeHandle private_nh;
	string port;
	int baudrate_, timeout_;
	private_nh.param("port", port, string("/dev/ttyACM0"));
	private_nh.param("baudrate", baudrate_, 9600);
	private_nh.param("timeout", timeout_, 1000);
	uint32_t baudrate = static_cast<uint32_t>(baudrate_);
	uint32_t timeout = static_cast<uint32_t>(timeout_);
 	serial::Timeout timeout_class = serial::Timeout::simpleTimeout(timeout);
 	m_serial.setPort(port);
 	m_serial.setBaudrate(baudrate);
 	m_serial.setTimeout(timeout_class);
	m_serial.open();
	cout << "Is the serial port open? ";
	if (m_serial.isOpen()) cout << "Yes." << endl;
	else cout << "No." << endl;
	m_service = nh.advertiseService("serial_command", &PGSDeviceDriver::command, this);
}

PGSDeviceDriver::~PGSDeviceDriver(){}

bool PGSDeviceDriver::command(PGSCmd::Request &req, PGSCmd::Response &res){
	if (req.valve_on == false){
		res.serial_cmd = to_string(res.RESET);
		m_serial.write(res.serial_cmd);
		return true;
	}
	else if ((req.valve_on != 0 && req.valve_on != 1) || (req.scalar < 0) || (req.scalar > 1)){
		ROS_ERROR("Command to PGS driver is invalid format. valve_on: 0 or 1, scalar: float on the interval [0,1]");
		return false;
	}
	string cmd = to_string(res.VALVE_OPEN)+findSerialCmd(req.scalar);
	m_serial.write(cmd);
	return true;
}

string PGSDeviceDriver::findSerialCmd(float scalar){
	float scalar10 = scalar * 10;
	char cmd;
	if (scalar10 != 10){
		cmd = static_cast<char>(PGSCmd::Response::P2 + floor(scalar10)-1);
	}
	else {
		cmd = static_cast<char>(PGSCmd::Response::P2 + PGSCmd::Response::num_interval - 1);
	}
	return string(1,cmd);
}
