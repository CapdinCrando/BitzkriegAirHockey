//Xbox Controller Parser
//controller.cpp
//----------------------
//10/30/2019
//Gavin Mullis

//Header File
#include 'controller.h'

//Headers
#include <sys/types.h>	//Defines special data types (C)
#include <sys/stat.h>	//Defines the structure of data  (C)
#include <fcntl.h>		//File control (C)
#include <iostream>		//Input/Output Streams (C++)
#include <string>		//Strings (C++)
#include <sstream>		//Provides string stream classes (C++)
#include "unistd.h"		//Various constant, types, and function declarations; ie NULL, I/O functions, size... (C)

Controller::Controller()
{
	openPath("/dev/input/js0");	//May not be the correct location
}

Controller::Controller(int controllerNumber)
{
	std::stringstream sstm;	//Init String Stream
	sstm << "/dev/input/js" << controllerNumber;	//Adds controllerNumber to end of location
	openPath(sstm.str());
}

Controller::Controller(std::string devicePath)
{
	openPath(devicePath);
}

Controller::Controller(std::string devicePath, bool blocking)
{
	openPath(devicePath, blocking);
}

void Controller::openPath(std::string devicePath, bool blocking)
{
	//Open device using either blocking or non-blocking
	_fd = open(devicePath.c_str(), blocking ? O_RDONLY : O_RDONLY | O_NONBLOCK);
}

bool Controller::sample(ControllerEvent* event)
{
	int bytes = read(_fd, event, sizeof(*event));

	if (bytes == -1)
	{
		return false;	//If this event occurs, controller is likely out of sync and this controller instance is unusable
	}

	return bytes == sizeof(*event);
}

bool Controller::isFound()
{
	return _fd >= 0;
}

Controller::~Controller()
{
	close(_fd);
}

std::ostream& operator<<(std::ostream& os, const ControllerEvent& e)
{
	os << endl;
	os << "Type: " << static_cast<int>(e.type) << endl;
	os << "Number: " << static_cast<int>(e.number) << endl;
	os << "Value: " << static_cast<int>(e.value) << endl;

	return os;
}
