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

	Application *app = new Application();
	app->initialization();
	app->createShaders();
	
	app->createModels();

	return app->run();
	
}