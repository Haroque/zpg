#include "Scene.h"
#include "DrawableObject.h"
#include "Model.h"
#include "Shader.h"
#include "ShaderProgram.h"

#include <glad/gl.h>

#include <iterator>

#include "Models/sphere.h"
#include "Models/suzi_smooth.h"

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::createShaders()
{
	// Index 0: Sphere (červená)
    Shader sphereVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader sphereFragmentShader(GL_FRAGMENT_SHADER, "shaders/red.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(sphereVertexShader), std::move(sphereFragmentShader)));

    // Index 1: Suzi (modrá)
    Shader suziVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader suziFragmentShader(GL_FRAGMENT_SHADER, "shaders/blue.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(suziVertexShader), std::move(suziFragmentShader)));

    // Index 2: Duhový (základní barvy z vrcholů pro trojúhelník a čtverec)
    Shader rainbowVertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
    Shader rainbowFragmentShader(GL_FRAGMENT_SHADER, "shaders/basic.frag");
    shaderPrograms_.push_back(std::make_unique<ShaderProgram>(
        std::move(rainbowVertexShader), std::move(rainbowFragmentShader)));
}

void Scene::createModels(int mode)
{
	if(mode == 1)
	{
		// 1. trojuhelnik
		std::vector<float> triangleData = {
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		auto triangleModel = std::make_unique<Model>(triangleData, 3, GL_TRIANGLES);
		drawableObjects_.push_back(std::make_unique<DrawableObject>(*shaderPrograms_[2], std::move(triangleModel)));
	}
	else if(mode == 2)
	{
		// 3. Vytvoření čtverce se žlutým vrcholem
		std::vector<float> squareData = {
			-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, //   1
			-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, //   2
			0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, //  3
			0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f  //             4 
		};
		auto squareModel = std::make_unique<Model>(squareData, 4, GL_TRIANGLE_STRIP);
		drawableObjects_.push_back(std::make_unique<DrawableObject>(*shaderPrograms_[2], std::move(squareModel)));
	}
	else if(mode == 3)
	{
		if (shaderPrograms_.size() < 2) //suzi
			return;

		std::vector<float> suziData(suziSmooth, suziSmooth + sizeof(suziSmooth) / sizeof(float));
		auto suziModel = std::make_unique<Model>(suziData, static_cast<int>(suziData.size() / 6), GL_TRIANGLES);
		auto suziObject = std::make_unique<DrawableObject>(*shaderPrograms_[1], std::move(suziModel));
		suziObject->setPosition(glm::vec3(0.8f, 0.0f, 0.0f));
		drawableObjects_.push_back(std::move(suziObject));
	}
	else if(mode == 4)
	{
		if (shaderPrograms_.empty()) //sphere
			return;

		std::vector<float> sphereData(sphere, sphere + sizeof(sphere) / sizeof(float));
		auto sphereModel = std::make_unique<Model>(sphereData, static_cast<int>(sphereData.size() / 6), GL_TRIANGLES);
		auto sphereObject = std::make_unique<DrawableObject>(*shaderPrograms_[0], std::move(sphereModel));
		sphereObject->setPosition(glm::vec3(-0.8f, 0.0f, 0.0f));
		drawableObjects_.push_back(std::move(sphereObject));
	}
}

void Scene::update()
{
    for (auto& obj : drawableObjects_)
        obj->update();
}

void Scene::setRotationDirection(float direction)
{
    for (auto& obj : drawableObjects_)
        obj->setRotationDirection(direction);
}

void Scene::render()
{
	for (auto& obj : drawableObjects_)
    {
        if (obj->isVisible())
        {
            obj->draw();
        }
    }
}