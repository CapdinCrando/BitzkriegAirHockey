//Xbox Controller DEMO
//controllerDEMO.cpp
//----------------------
//10/30/2019
//Gavin Mullis

//Header File
#include "controller.h"

//Headers
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv)
{
	//Create an instance of Controller
	Controller controller0("dev/input/js0");	//Might not be the correct location or controller name

	//Ensure Controller was found and opened
	if (!controller0.isFound())
	{
		printf("Controller was not found at specified location or failed to open correctly.\n");
		printf("Exiting Now...\n");
		exit(1);
	}

	while (true)
	{
		//Restrict Sample Rate
		usleep(1000);

		//Attempt to get sample from Controller
		ControllerEvent event;
		if (controller0.sample(&event))
		{
			std::cout << endl << "Initial State: " << event.isInitState() << " (True If Initial Event)"<< endl;

			if (event.isButton())
			{
				std::cout << "Button Number: " << (int)event.number << endl;
				std::cout << "Button Value: " << ((event.value == 0) ? "Up" : "Down") << endl;
			}

			else if (event.isAxis())
			{
				std::cout << "Axis Number: " << (int)event.number << endl;
				std::cout << "Axis Value: " << (int)event.value << endl;
			}

			else
			{
				std::cout << "This is an undefined event... Yikes!" << endl;
			}
		}

		else
		{
			std::cout << endl << "Failed to get sample from Controller... Oof!" << endl;
		}
	}
}
