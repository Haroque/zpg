#pragma once

#include <memory>
#include <vector>

using namespace std;

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

	void setRotationDirection(int direction);
	void render();

private:
	vector<unique_ptr<ShaderProgram>> shaderPrograms_;
	vector<unique_ptr<DrawableObject>> drawableObjects_;

};

