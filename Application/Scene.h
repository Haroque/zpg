#pragma once

#include <memory>

class DrawableObject;
class ShaderProgram;

class Scene
{
public:
	Scene();
	~Scene();

	void createShaders();
	void createModels();
	void render() const;

private:
	std::unique_ptr<ShaderProgram> shaderProgram_;
	std::unique_ptr<DrawableObject> drawableObject_;
};

