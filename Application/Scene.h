/*
 * Antonin Harok HAR0199
 *
 * File: Scene.h
 * Description:  Header file for the Scene class
 */

#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Camera.h"

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

    void windowResize(int width, int height);

    void triangleScene(glm::vec3 position = glm::vec3(0.5f, 0.0f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f),
        float rotationAngle = 0.0f,
        glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f),
        float rotationSpeed = 0.02f,
        int shaderIndex = 2);

    void squareScene(glm::vec3 position = glm::vec3(0.0f),
        glm::vec3 scale = glm::vec3(1.0f),
        float rotationAngle = 0.0f,
        glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f),
        float rotationSpeed = 0.0f,
        int shaderIndex = 2);

    void sphereScene(glm::vec3 position = glm::vec3(0.0f),
        glm::vec3 scale = glm::vec3(1.0f),
        float rotationAngle = 0.0f,
        glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f),
        float rotationSpeed = 0.0f,
        int shaderIndex = 6);

    void treeScene(glm::vec3 position = glm::vec3(0.0f),
        glm::vec3 scale = glm::vec3(1.0f),
        float rotationAngle = 0.0f,
        glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f),
        float rotationSpeed = 0.0f,
        int shaderIndex = 6);

    void bushScene(glm::vec3 position = glm::vec3(0.0f),
        glm::vec3 scale = glm::vec3(1.0f),
        float rotationAngle = 0.0f,
        glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f),
        float rotationSpeed = 0.0f,
        int shaderIndex = 3);

    void signatureScene(glm::vec3 position = glm::vec3(0.5f, -0.8f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f),
        float rotationAngle = 0.0f,
        glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f),
        float rotationSpeed = 0.0f,
        int shaderIndex = 1);

    void clockScene(glm::vec3 position = glm::vec3(0.5f, 0.8f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f),
        float rotationAngle = 0.0f,
        glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f),
        float rotationSpeed = 0.0f,
        int shaderIndex = 4);

    void groundScene(glm::vec3 position = glm::vec3(0.0f, -0.05f, 0.0f),
        glm::vec3 scale = glm::vec3(30.0f, 30.0f, 1.0f),
        float rotationAngle = -glm::half_pi<float>(),
        glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f),
        float rotationSpeed = 0.0f,
        int shaderIndex = 5);

    void planetsScene(glm::vec3 position = glm::vec3(0.0f),
        glm::vec3 scale = glm::vec3(1.0f),
        float rotationAngle = 0.0f,
        glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f),
        float rotationSpeed = 0.05f,
        int shaderIndex = 6);

	void alienScene(glm::vec3 position = glm::vec3(0.0f),
		glm::vec3 scale = glm::vec3(1.0f),
		float rotationAngle = 0.0f,
		glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f),
		float rotationSpeed = 0.05f,
		int shaderIndex = 6);

private:
	std::vector<std::unique_ptr<ShaderProgram>> shaderPrograms_;
	std::vector<std::unique_ptr<DrawableObject>> drawableObjects_;
	std::unique_ptr<Camera> camera_;

	void createShaderProgram(const char* vertexPath, const char* fragmentPath);
};
