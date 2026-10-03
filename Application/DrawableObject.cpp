/*
 * Antonin Harok HAR0199
 *
 * File: DrawableObject.cpp
 * Description:  Implementation file for the DrawableObject class
 */

#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Model.h"

DrawableObject::DrawableObject(ShaderProgram& shaderProgram, Model& model)
	: shaderProgram_(shaderProgram), model_(model), position_(0.0f), rotationAngle_(0.0f), rotationDirection_(0)
{
}


void DrawableObject::update()
{
	rotationAngle_ += rotationDirection_ * 0.01f;
}

void DrawableObject::setRotationDirection(int direction)
{
	rotationDirection_ = direction;
}

void DrawableObject::setPosition(const glm::vec3& position)
{
	position_ = position;
}

void DrawableObject::setScale(const glm::vec3& scale)
{
	scale_ = scale;
}

void DrawableObject::draw() 
{
	shaderProgram_.use();
	shaderProgram_.setUniform("Position", position_);
	shaderProgram_.setUniform("Scale", scale_);
	shaderProgram_.setUniform("Rotation", rotation_);

	model_.draw();
}