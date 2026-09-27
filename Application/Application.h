#pragma once
struct GLFWwindow;
class Scene;

class Application
{
public:
	Application();
	~Application();

	//Application(const Application&) = delete;
	//Application& operator=(const Application&) = delete;

	void initialization();
	void createShaders();
	void createModels(int mode);
	int run();
	void setRotationDirection(float direction);

private:
	static void errorCallback(int error, const char* description);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void windowSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* window_ = nullptr;
	Scene* scene_ = nullptr;
};
