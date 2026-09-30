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
		
		app.createModels(3);
		//app.createModels(4);
		return app.run();
	}
	catch (const std::exception& error)
	{
		std::cerr << "Application startup failed: " << error.what() << '\n';
		return EXIT_FAILURE;
	}
}