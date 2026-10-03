/*
 * Antonin Harok HAR0199
 *
 * File: DrawableObject.h
 * Description:  Header file for the DrawableObject class
 */

#pragma once
#include <memory>
#include <glm/vec3.hpp>
#include "Model.h"

class ShaderProgram;


class DrawableObject
{
public:
	DrawableObject(ShaderProgram& shaderProgram, Model& model);

	void draw();
	void update();

	void setRotationDirection(int direction);
	void setPosition(const glm::vec3& position);
	


private:
	ShaderProgram& shaderProgram_;
	Model& model_;

	int rotationDirection_ = 0; // 1 for clockwise, -1 for counter-clockwise, 0 for no rotation
	float rotationAngle_ = 0.0f;
	glm::vec3 position_ = glm::vec3(0.0f);
};
