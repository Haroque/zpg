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

void Scene::createModels()
{
	if (shaderProgram_)
		drawableObject_ = std::make_unique<DrawableObject>(*shaderProgram_);
}

void Scene::render() const
{
	if (drawableObject_)
		drawableObject_->draw();
}
