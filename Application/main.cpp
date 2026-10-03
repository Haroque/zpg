/*
 * Antonin Harok HAR0199
 *
 * File: main.cpp
 * Description:  Main application file for the Applicatin class
 */

#include "Application.h"
#include <cstdlib>
#include <exception>
#include <iostream>

int main(void)
{
	try
	{
		Application app;
		app.initialization();
		app.createShaders();
		
		//app.createModels(1);
		app.createModels(5);

		return app.run();
	}
	catch (const std::exception& error)
	{
		std::cerr << "Application startup failed: " << error.what() << '\n';
		return EXIT_FAILURE;
	}
}