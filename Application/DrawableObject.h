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
#include "Transformation.h"

class ShaderProgram;


class DrawableObject
{
public:
	DrawableObject(ShaderProgram& shaderProgram, Model& model);
	
	void draw();
	void update();

	void setRotationDirection(int direction);
	void setTransformation(std::shared_ptr<Transformation> transformation) { transformation_ = transformation; }

	void setMaterial(float shininess)
	{
		shininess_ = shininess;
	}

private:
	ShaderProgram& shaderProgram_;
	Model& model_;

	std::shared_ptr<Transformation> transformation_ = nullptr;

	//default value
	float shininess_ = 32.0f;
};
