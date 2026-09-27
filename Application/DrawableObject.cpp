#include "DrawableObject.h"

#include "ShaderProgram.h"

DrawableObject::DrawableObject(ShaderProgram& shaderProgram, std::unique_ptr<Model> model)
	: shaderProgram_(shaderProgram), model_(std::move(model))
{
}

void DrawableObject::update()
{
	transformation_.update();
}

void DrawableObject::setRotationDirection(float direction)
{
	transformation_.setRotationDirection(direction);
}

void DrawableObject::setPosition(const glm::vec3& position)
{
	transformation_.setPosition(position);
}

void DrawableObject::draw()
{
	shaderProgram_.use();
	shaderProgram_.setTransformation(transformation_);
	model_->draw();
}