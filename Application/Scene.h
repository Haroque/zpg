/*
 * Antonin Harok HAR0199
 *
 * File: Scene.h
 * Description:  Header file for the Scene class
 */

#pragma once
#include <memory>
#include <vector>

#include "Camera.h"

using namespace std;

class DrawableObject;
class ShaderProgram;


class Scene
{
public:
	Scene();
	~Scene();

	void createShaders();
	void createModels(int mode = 1);
	void clearModels();
	void update();

	void setRotationDirection(int direction);
	void moveCamera(int direction);
	void rotateCamera(float xpos, float ypos);
	void render();

	void signature();
	void planets(glm::vec3 basePosition = glm::vec3(0.0f), float baseScale = 1.0f);
	void clock();
	void groundSetup();

private:
	vector<unique_ptr<ShaderProgram>> shaderPrograms_;
	vector<unique_ptr<DrawableObject>> drawableObjects_;
	unique_ptr<Camera> camera_;
};
