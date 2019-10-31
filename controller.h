//Xbox Controller Parser
//controller.h
//----------------------
//10/30/2019
//Gavin Mullis

//Opening Guard
#ifndef __CONTROLLER_HH__
#define __CONTROLLER_HH__

//Headers
#include <string>
#include <iostream>

//--------------------------------------------------------------------------------------------------

//Macros for Events
#define EVENT_BUTTON 0x01	//Button pressed/released
#define EVENT_AXIS	 0x02	//Joystick Moved
#define EVENT_INIT	 0x03	//Initial State of Controller

//For handling of a given sampled joystick event
class ControllerEvent
{
public:
	//Axis Constants
	static const short MIN_AXES_VALUE = -32768;	//Min for Axis Range
	static const short MAX_AXES_VALUE = 32768;	//Max for Axis Range

	//Can Pertain to Joystick or Buttons; 
	//For Button Inputs [1 or 0], (Down or Up)
	//For Axis Inputs [-32768, 32768] Range
	short value;

	//Event Type
	unsigned char type;

	//Axis or Button Number
	unsigned char number;

	//Returns True, if event is caused by a button press
	bool isButton()
	{
		return (type & EVENT_BUTTON) != 0;
	}

	//Returns True, if the event is caused by axis movement
	bool isAxis()
	{
		return (type & EVENT_AXIS) != 0;
	}

	//Returns True, if the event is caused by the controller's initial connection
	bool isInitState()
	{
		return (type & EVENT_INIT) != 0;
	}

	//ostream inserter must be a friend to access internals of ControllerEvent class
	friend std::ostream& operator<<(std::ostream& os, const ControllerEvent& e);
};

//Stream insertion function so you can type lines like
//		'cout << event1 << endl;'
std::ostream& operator<<(std::ostream& os, const ControllerEvent& e);

//--------------------------------------------------------------------------------------------------

//Represents a given Controller
class Controller
{
private:
	//For Opening Path to Controller
	void openPath(std::string devicePath, bool blocking = false);

	//For Opening Device (File Descriptor)
	int _fd;

public:
	~Controller();	//Destructor

	//Constructors
	Controller();						//Init an instance of a controller at location 'dev/input/js0'
	Controller(int controllerNumber);	//Init an instance of a controller with specified zero-indexed number ie 'dev/input/jsx' where x is int
	Controller(std::string devicePath); //Init an instance of a controller with specified location

	Controller(Controller const&) = delete;	//Blocking controllers from being copied
	Controller(Controller &&) = default;	//Allowing controllers to be moved

	Controller(std::string devicePath, bool blocking);	//Init with optional blocking for I/O

	//Observers
	bool isFound();	//Returns True, if Controller was found and can be used

	//Attempts to populate a ControllerEvent with sampled data from Controller
	bool sample(ControllerEvent* event);	//Returns True, if data is avaliable	
};

//Closing Guard
#endif
