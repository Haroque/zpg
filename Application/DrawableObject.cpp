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
	: shaderProgram_(shaderProgram), model_(model), translation_(0.0f), scale_(1.0f), rotation_(0.0f), rotationDirection_(0)
{
}


void DrawableObject::update()
{
	rotation_ += rotationDirection_ * 0.01f;
}

void DrawableObject::setRotationDirection(int direction)
{
	rotationDirection_ = direction;
}

void DrawableObject::setTranslation(const glm::vec3& translation)
{
	translation_ = translation;
}

void DrawableObject::setScale(const glm::vec3& scale)
{
	scale_ = scale;
}

void DrawableObject::draw() 
{
	shaderProgram_.use();
	shaderProgram_.setUniform("Translation", translation_);
	shaderProgram_.setUniform("Scale", scale_);
	shaderProgram_.setUniform("Rotation", rotation_);

	model_.draw();
}