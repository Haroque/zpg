#include "DrawableObject.h"

#include "ShaderProgram.h"

DrawableObject::DrawableObject(ShaderProgram& shaderProgram)
	: shaderProgram_(shaderProgram)
{
}

void DrawableObject::draw() const
{
	shaderProgram_.use();
	model_.draw();
}
