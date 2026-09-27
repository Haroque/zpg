#include "Scene.h"
#include "DrawableObject.h"
#include "Shader.h"
#include "ShaderProgram.h"

#include <glad/gl.h>

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::createShaders()
{
	Shader vertexShader(GL_VERTEX_SHADER, "shaders/basic.vert");
	Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/basic.frag");
	shaderProgram_ = std::make_unique<ShaderProgram>(std::move(vertexShader), std::move(fragmentShader));
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
		auto triangleModel = std::make_unique<Model>(triangleData, 3);
		drawableObjects_.push_back(std::make_unique<DrawableObject>(*shaderProgram_, std::move(triangleModel)));
	}
	else if(mode == 2)
	{
		// 3. Vytvoření čtverce se žlutým vrcholem
		std::vector<float> squareData = {
			-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 
			-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 
			0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 

			-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 
			0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 
			0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f  
		};
		auto squareModel = std::make_unique<Model>(squareData, 6);
		drawableObjects_.push_back(std::make_unique<DrawableObject>(*shaderProgram_, std::move(squareModel)));
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