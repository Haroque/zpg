/*
 * Antonin Harok HAR0199
 *
 * File: Application.h
 * Description:  Header file for the Applicatin class
 */

#pragma once
#include <memory>

struct GLFWwindow;
class Scene;

class Application
{
public:
	Application();
	~Application();

	void initialization();
	void createShaders();
	void createModels(int mode=1);
	void setScene(int mode);
	int run();
	void setRotationDirection(int direction);
	void moveCamera(int direction);

	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	void rotateCamera(float xpos, float ypos);
	void windowResize(int width, int height);

private:
	static void errorCallback(int error, const char* description);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void windowSizeCallback(GLFWwindow* window, int width, int height);
	

	GLFWwindow* window_ = nullptr;
	std::unique_ptr<Scene> scene_;

	bool rightMouseButtonPressed_ = false;
	double lastMouseX_ = 0.0;
	double lastMouseY_ = 0.0;

};
