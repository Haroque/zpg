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

#include "TransformationComposite.h"
#include "TransformationLeaf.h"

#include <glad/gl.h>
#include <iterator>
#include <vector>
#include <memory>
#include <random>

#include "Models/sphere.h"
#include "Models/suzi_smooth.h"
#include "Models/login.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/moon.h"
#include "Models/sun.h"
#include "Models/earth.h"

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::createShaders()
{
	// Index 0: Red 
    Shader sphereVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader sphereFragmentShader(GL_FRAGMENT_SHADER, "shaders/red.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(sphereVertexShader), std::move(sphereFragmentShader)));

    // Index 1: Blue 
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
		static Model triangleModel(triangleData, 3, GL_TRIANGLES);
		auto triangle = std::make_unique<DrawableObject>(*shaderPrograms_[2], triangleModel);
		auto composite = std::make_shared<TransformationComposite>();
		
		composite->addTransformation(std::make_shared<Rotate>(0.0f, glm::vec3(0.0f, 0.0f, 1.0f), 0.02f));
		composite->addTransformation(std::make_shared<Translate>(glm::vec3(0.5f, 0.0f, 0.0f)));
		

		triangle->setTransformation(composite);
		drawableObjects_.push_back(std::move(triangle));
		signature();
	}
	else if(mode == 2)
	{
		if (shaderPrograms_.empty()) //sphere
			return;

		static std::vector<float> sphereData(sphere, sphere + sizeof(sphere) / sizeof(float));
		static Model sphereModel(sphereData, static_cast<int>(sphereData.size() / 6), GL_TRIANGLES);

		auto sphereObject = std::make_unique<DrawableObject>(*shaderPrograms_[0], sphereModel);
		auto composite = std::make_shared<TransformationComposite>();
		composite->addTransformation(std::make_shared<Translate>(glm::vec3(0.0f, 0.0f, 0.0f)));
		composite->addTransformation(std::make_shared<Scale>(glm::vec3(0.5f)));
		sphereObject->setTransformation(composite);

		drawableObjects_.push_back(std::move(sphereObject));
		signature();
	}
	else if(mode == 3)
	{
		
		static std::vector<float> treeData(tree, tree + sizeof(tree) / sizeof(float));
		static std::vector<float> bushData(bushes, bushes + sizeof(bushes) / sizeof(float));
		static Model treeModel(treeData, static_cast<int>(treeData.size() / 6), GL_TRIANGLES);
		static Model bushModel(bushData, static_cast<int>(bushData.size() / 6), GL_TRIANGLES);
	
	
		for (int i = 0; i < 12; i++)
		{
			auto treeObj = std::make_unique<DrawableObject>(*shaderPrograms_[2], treeModel);
			auto trans = std::make_shared<TransformationComposite>();
			
			//from 0 to 199, scale from 0.1 to 0.2
			float posX = (rand() % 200) / 100.0f - 1.0f;
			float posY = (rand() % 200) / 100.0f - 1.0f;
			float scale = (rand() % 10) / 100.0f + 0.1f;
			
			trans->addTransformation(std::make_shared<Translate>(glm::vec3(posX, posY, 0.0f)));
			trans->addTransformation(std::make_shared<Scale>(glm::vec3(scale)));

			treeObj->setTransformation(trans);
			drawableObjects_.push_back(std::move(treeObj));

		}
		for (int i = 0; i < 15; i++)
		{
			auto bushObj = std::make_unique<DrawableObject>(*shaderPrograms_[0], bushModel);
			auto trans = std::make_shared<TransformationComposite>();

			float posX = (rand() % 200) / 100.0f - 1.0f;
			float posY = (rand() % 200) / 100.0f - 1.0f;
			float scale = (rand() % 10) / 100.0f + 0.1f;

			trans->addTransformation(std::make_shared<Translate>(glm::vec3(posX, posY, 0.0f)));
			trans->addTransformation(std::make_shared<Scale>(glm::vec3(scale)));

			bushObj->setTransformation(trans);
			drawableObjects_.push_back(std::move(bushObj));
		}

	}
	else if (mode == 4) //login
	{
		static std::vector<float> LoginData(login, login + sizeof(login) / sizeof(float));
		static Model LoginModel(LoginData, static_cast<int>(LoginData.size() / 6), GL_TRIANGLES);

		auto LoginObject = std::make_unique<DrawableObject>(*shaderPrograms_[1], LoginModel);
		LoginObject->setTransformation(std::make_shared<Translate>(glm::vec3(0.0f, 0.0f, 0.0f)));
		drawableObjects_.push_back(std::move(LoginObject));
	}
	else if (mode == 5) 
	{
		// square with 4th vextex color (yellow) and using GL_TRIANGLE_STRIP
		std::vector<float> squareData = {
			-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, //   1
			-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, //   2
			0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, //  3
			0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f  //             4 
		};
		static Model squareModel(squareData, 4, GL_TRIANGLE_STRIP);
		drawableObjects_.push_back(std::make_unique<DrawableObject>(*shaderPrograms_[2], squareModel));
		signature();
	}
	else if (mode == 6)
	{
		static std::vector<float> sunData(sun, sun + sizeof(sun) / sizeof(float));
		static std::vector<float> earthData(earth, earth + sizeof(earth) / sizeof(float));
		static std::vector<float> moonData(moon, moon + sizeof(moon) / sizeof(float));

		static Model sunModel(sunData, static_cast<int>(sunData.size() / 6), GL_TRIANGLES);
		static Model earthModel(earthData, static_cast<int>(earthData.size() / 6), GL_TRIANGLES);
		static Model moonModel(moonData, static_cast<int>(moonData.size() / 6), GL_TRIANGLES);

	}
}

void Scene::signature()
{
	static std::vector<float> LoginData(login, login + sizeof(login) / sizeof(float));
	static Model LoginModel(LoginData, static_cast<int>(LoginData.size() / 6), GL_TRIANGLES);

	auto LoginObject = std::make_unique<DrawableObject>(*shaderPrograms_[1], LoginModel);

	auto composite = std::make_shared<TransformationComposite>();
	composite->addTransformation(std::make_shared<Translate>(glm::vec3(0.5f, -0.8f, 0.0f)));
	composite->addTransformation(std::make_shared<Scale>(glm::vec3(0.1f)));
	LoginObject->setTransformation(composite);

	drawableObjects_.push_back(std::move(LoginObject));
}


void Scene::clearModels()
{
	drawableObjects_.clear();
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