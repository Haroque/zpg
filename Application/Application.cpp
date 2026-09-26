
 //Include GLAD
 //Only define this in one file
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

 //Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
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

void Application::createModels()
{
    if (!scene_)
        scene_ = new Scene();
    scene_->createModels();
}

int Application::run()
{
    while (!glfwWindowShouldClose(window_))
    {
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

void Application::keyCallback(GLFWwindow* window, int, int, int action, int)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Application::windowSizeCallback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}