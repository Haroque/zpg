#include "Application.h"
int main(void)
{
	Application* app = new Application();
	app->initialization(); //OpenGL inicialization

	//Loading scene
	app->createShaders();
	//app->createModels(1); 
	//app->createModels(2); 
	app->createModels(3);
	app->createModels(4);
	app->run(); //Rendering 
}