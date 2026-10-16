#include <glad/gl.h>
#include <iterator>
#include <vector>
#include <memory>
#include <random>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "ShaderProgram.h"

Camera::Camera(ShaderProgram* shaderProgram)
	: shaderProgram_(shaderProgram),
		eye(glm::vec3(0.0f, 0.0f, 3.0f)),
		up(glm::vec3(0.0f, 1.0f, 0.0f)),
		alpha(glm::half_pi<float>()),        // 90 
		phi(-glm::half_pi<float>()),       // -90
		fov(glm::radians(60.0f)),
		aspect(800.0f / 600.0f),
		zNear(0.1f),
		zFar(100.0f)
{
	updateTarget();
}


void Camera::updateTarget()
{
	if (alpha < 0.1f) alpha = 0.1f;
	if (alpha > glm::pi<float>() - 0.1f) alpha = glm::pi<float>() - 0.1f;

	target.x = sin(alpha) * cos(phi);
	target.z = sin(alpha) * sin(phi);
	target.y = cos(alpha);
	
	// 
	target = glm::normalize(target);
}

glm::mat4 Camera::getCamera(void) {
	return glm::lookAt(eye, eye + target, up);
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(eye, eye + target, up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::updateShaderProgram(ShaderProgram& shaderProgram)
{
	shaderProgram.use();
	shaderProgram.setUniform("viewMatrix", getViewMatrix());
	shaderProgram.setUniform("projectionMatrix", getProjectionMatrix());
	
}


void Camera::moveForward(float speed)
{
	eye += target * speed;
}

void Camera::moveBackward(float speed)
{
	eye -= target * speed;
}

void Camera::moveLeft(float speed)
{
	glm::vec3 right = glm::normalize(glm::cross(target, up));
	eye -= right * speed;
}

void Camera::moveRight(float speed)
{
	glm::vec3 right = glm::normalize(glm::cross(target, up));
	eye += right * speed;
}