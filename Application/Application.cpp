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

#include "Application.h"
#include "Scene.h"

Application::Application() = default;

Application::~Application()
{
    delete scene_;
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

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
        std::exit(EXIT_FAILURE);

    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(window_, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}

void Application::createShaders()
{
    if (!scene_)
        scene_ = new Scene();
    scene_->createShaders();
}

void Application::createModels(int mode)
{
    if (!scene_)
        scene_ = new Scene();
    scene_->createModels(mode);
}

void Application::setScene(int mode)
{
	if (!scene_)
		return;
	scene_->clearModels();
	scene_->createModels(mode);
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

void Application::setRotationDirection(int direction)
{
    if (scene_)
        scene_->setRotationDirection(direction);
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
    
        if (key == GLFW_KEY_LEFT || key == GLFW_KEY_UP)
        {
            application->setRotationDirection(-1);
        }
        else if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_DOWN)
        {
            application->setRotationDirection(1);
        }
		else if (key >=GLFW_KEY_1 && key <= GLFW_KEY_6)
		{
            application->setScene(key - GLFW_KEY_0);
		}
    }
}

void Application::windowSizeCallback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height); 
}