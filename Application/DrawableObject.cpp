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

void DrawableObject::draw()
{
	shaderProgram_.use();
	GLuint programId = shaderProgram_.getId();

	// Translation uniform, 
    GLint posLocation = glGetUniformLocation(programId, "uPosition");
    if (posLocation != -1)
    {
        glUniform3f(posLocation, position_.x, position_.y, position_.z);
    }

	// Rotation uniform, without matrix
    GLint rotLocation = glGetUniformLocation(programId, "uRotationAngle");
    if (rotLocation != -1)
    {
        glUniform1f(rotLocation, rotationAngle_);
    }

	// Color uniform
    GLint colorLocation = glGetUniformLocation(programId, "fragmentColor");
    if (colorLocation != -1)
    {
        glUniform3f(colorLocation, 1.0f, 0.0f, 0.0f); // Červená barva
    }

	model_.draw();
}