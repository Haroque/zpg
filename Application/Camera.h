#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class ShaderProgram;

class Camera
{
public:
    Camera(ShaderProgram* shaderProgram);
	glm::mat4 getCamera(void);

	void updateShaderProgram(ShaderProgram& shaderProgram);
	void updateTarget();

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

	void moveForward(float speed);
	void moveBackward(float speed);
	void moveLeft(float speed);
	void moveRight(float speed);



private: 
	ShaderProgram* shaderProgram_;
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;

	float fov; //radians
	float aspect;
	float zNear;
	float zFar;

	float alpha;
	float phi;

	float speed = 0.1;

};

