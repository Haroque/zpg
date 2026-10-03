/*
 * Antonin Harok HAR0199
 *
 * File: Scene.cpp
 * Description:  Implementation file for the Scene class
 */

#include "Scene.h"
#include "DrawableObject.h"
#include "Model.h"
#include "Shader.h"
#include "ShaderProgram.h"

#include <glad/gl.h>
#include <iterator>

#include "Models/sphere.h"
#include "Models/suzi_smooth.h"
#include "Models/login.h"

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::createShaders()
{
	// Index 0: Sphere 
    Shader sphereVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader sphereFragmentShader(GL_FRAGMENT_SHADER, "shaders/red.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(sphereVertexShader), std::move(sphereFragmentShader)));

    // Index 1: Suzi 
    Shader suziVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader suziFragmentShader(GL_FRAGMENT_SHADER, "shaders/blue.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(suziVertexShader), std::move(suziFragmentShader)));

	// Index 2: rainbow (basic colors from vertices for triangle and square)
    Shader rainbowVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader rainbowFragmentShader(GL_FRAGMENT_SHADER, "shaders/basic.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(rainbowVertexShader), std::move(rainbowFragmentShader)));
}

void Scene::createModels(int mode)
{
	if(mode == 1)
	{
		// 1. triangle with vertex colors
		std::vector<float> triangleData = {
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		auto triangleModel = std::make_unique<Model>(triangleData, 3, GL_TRIANGLES);
		drawableObjects_.push_back(std::make_unique<DrawableObject>(*shaderPrograms_[2], *triangleModel));
	}
	else if(mode == 2)
	{
		// 3. square with 4th vextex color (yellow) and using GL_TRIANGLE_STRIP
		std::vector<float> squareData = {
			-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, //   1
			-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, //   2
			0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, //  3
			0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f  //             4 
		};
		auto squareModel = std::make_unique<Model>(squareData, 4, GL_TRIANGLE_STRIP);
		drawableObjects_.push_back(std::make_unique<DrawableObject>(*shaderPrograms_[2], *squareModel));
	}
	else if(mode == 3)
	{
		if (shaderPrograms_.size() < 2) //suzi
			return;

		std::vector<float> suziData(suziSmooth, suziSmooth + sizeof(suziSmooth) / sizeof(float));
		static Model suziModel(suziData, static_cast<int>(suziData.size() / 6), GL_TRIANGLES);

		auto suziObject = std::make_unique<DrawableObject>(*shaderPrograms_[1], suziModel);
		suziObject->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		drawableObjects_.push_back(std::move(suziObject));
	}
	else if(mode == 4)
	{
		if (shaderPrograms_.empty()) //sphere
			return;

		static std::vector<float> sphereData(sphere, sphere + sizeof(sphere) / sizeof(float));
		static Model sphereModel(sphereData, static_cast<int>(sphereData.size() / 6), GL_TRIANGLES);
		
		auto sphereObject = std::make_unique<DrawableObject>(*shaderPrograms_[0], sphereModel);
		sphereObject->setPosition(glm::vec3(-0.8f, 0.0f, 0.0f));
		drawableObjects_.push_back(std::move(sphereObject));
	}
	else if (mode == 5)
	{
		static std::vector<float> LoginData(login, login + sizeof(login) / sizeof(float));
		static Model LoginModel(LoginData, static_cast<int>(LoginData.size() / 6), GL_TRIANGLES);

		auto LoginObject = std::make_unique<DrawableObject>(*shaderPrograms_[1], LoginModel);
		LoginObject->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		drawableObjects_.push_back(std::move(LoginObject));
	}
}

void Scene::update()
{
    for (auto& obj : drawableObjects_)
        obj->update();
}

void Scene::setRotationDirection(int direction)
{
    for (auto& obj : drawableObjects_)
        obj->setRotationDirection(direction);
}

void Scene::render()
{
	for (auto& obj : drawableObjects_)
    {
		obj->draw();
    }
}