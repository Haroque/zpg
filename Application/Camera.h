#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Subject.h"

class ShaderProgram;


class Camera : public Subject
{
public:
    Camera(ShaderProgram* shaderProgram = nullptr);

	void updateShaderProgram(ShaderProgram& shaderProgram);
	

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

	void moveForward(float speed);
	void moveBackward(float speed);
	void moveLeft(float speed);
	void moveRight(float speed);

	
	void setAspectRatio(float aspectRatio);
	void onMouseMove(float X, float Y);

	glm::vec3 getEye() const { return eye; }

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

	float speed = 0.5f;

	void updateTarget();

};

