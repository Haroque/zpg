#pragma once

#include <memory>
#include <vector>

class DrawableObject;
class ShaderProgram;

class Scene
{
public:
	Scene();
	~Scene();

	void createShaders();
	void createModels(int mode);
	void update();
	void setRotationDirection(float direction);
	void render();

private:
	std::vector<std::unique_ptr<ShaderProgram>> shaderPrograms_;
	std::vector<std::unique_ptr<DrawableObject>> drawableObjects_;
};

