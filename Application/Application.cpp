/*
 * Antonin Harok HAR0199
 *
 * File: Application.cpp
 * Description:  Implementation file for the Application class
 */
#define GLAD_GL_IMPLEMENTATION  //Only define this in one file
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <cassert>

#include "Application.h"
#include "Scene.h"

Application::Application() = default;

Application::~Application()
{
    if (window_)
        glfwDestroyWindow(window_);
    glfwTerminate();
}

void Application::initialization()
{
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit())
        std::exit(EXIT_FAILURE);

    window_ = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);
    if (!window_)
    {
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);
    
    glfwSetWindowUserPointer(window_, this);
    glfwSetKeyCallback(window_, keyCallback);
    glfwSetWindowSizeCallback(window_, windowSizeCallback);

    glfwSetMouseButtonCallback(window_, mouseCallback);
    glfwSetCursorPosCallback(window_, cursorPosCallback);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
        std::exit(EXIT_FAILURE);

    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(window_, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    //    
    glDisable(GL_CULL_FACE);
}

void Application::createShaders()
{
    if (!scene_)
        scene_ = std::make_unique<Scene>();
    scene_->createShaders();
}

void Application::createModels(int mode)
{
    if (!scene_)
        scene_ = std::make_unique<Scene>();
    scene_->createModels(mode);
}

void Application::setScene(int mode)
{
	if (!scene_)
		return;
	scene_->clearModels();
	scene_->createModels(mode);
}

void Application::setRotationDirection(int direction)
{
    if (scene_)
        scene_->setRotationDirection(direction);
}

void Application::moveCamera(int direction)
{
	if (scene_)
		scene_->moveCamera(direction);
 }

int Application::run()
{
    while (!glfwWindowShouldClose(window_))
    {
        if (scene_)
            scene_->update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (scene_)
            scene_->render();
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
    return 0;
}

void Application::errorCallback(int, const char* description)
{
    fputs(description, stderr);
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    printf("key callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
        assert(application && "Application pointer is null in keyCallback");

        if (key == GLFW_KEY_UP)
        {
            application->setRotationDirection(-1);
        }
        else if (key == GLFW_KEY_DOWN)
        {
            application->setRotationDirection(1);
        }
		else if (key >=GLFW_KEY_1 && key <= GLFW_KEY_7)
		{
            application->setScene(key - GLFW_KEY_0);
		}
        else if (key == GLFW_KEY_W)
        {
			application->moveCamera(0);
        }
        else if (key == GLFW_KEY_S)
        {
            application->moveCamera(1);
        }
        else if (key == GLFW_KEY_A)
        {
            application->moveCamera(2);
        }
        else if (key == GLFW_KEY_D)
        {
            application->moveCamera(3);
        }
    }
}

void Application::windowResize(int width, int height)
{
    if (scene_)
        scene_->windowResize(width, height);
}


void Application::windowSizeCallback(GLFWwindow* window, int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app)
    {
        app->windowResize(width, height);
    }
}

void  Application::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
        if (action == GLFW_PRESS)
        {
            application->rightMouseButtonPressed_ = true;
            glfwGetCursorPos(window, &application->lastMouseX_, &application->lastMouseY_);
        }
        else if (action == GLFW_RELEASE)
        {
            application->rightMouseButtonPressed_ = false;
        }
	}
}
void Application::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app || !app->rightMouseButtonPressed_)
        return;

	//difference between current and last mouse position !
    float deltaX = static_cast<float>(xpos - app->lastMouseX_);
    float deltaY = static_cast<float>(ypos - app->lastMouseY_);

    app->lastMouseX_ = xpos;
    app->lastMouseY_ = ypos;
    app->rotateCamera(deltaX, deltaY);
}
void Application::rotateCamera(float xpos, float ypos)
{
    if (scene_)
        scene_->rotateCamera(xpos, ypos);
}