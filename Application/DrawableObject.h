#pragma once

#include "Model.h"
#include "Transformation.h"

class ShaderProgram;

class DrawableObject
{
public:
	explicit DrawableObject(ShaderProgram& shaderProgram);

	void draw() const;

private:
	ShaderProgram& shaderProgram_;
	Model model_;
	Transformation transformation_;
};

