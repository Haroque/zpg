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
	: shaderProgram_(shaderProgram), model_(model)
{
}


void DrawableObject::update()
{
	if (transformation_) {
		transformation_->update();
	}
}


void DrawableObject::draw() 
{
	shaderProgram_.use();
	glm::mat4 modelMatrix= glm::mat4(1.0f);

	if (transformation_) {
		modelMatrix = transformation_->getMatrix();
	}

	shaderProgram_.setUniform("modelMatrix", modelMatrix);

	model_.draw();
}
void DrawableObject::setRotationDirection(int direction)
{
	if (transformation_) {
		transformation_->setRotationDirection(direction);
	}
}