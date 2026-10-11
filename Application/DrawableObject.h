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


	void setTransformation(std::shared_ptr<Transformation> transformation) { transformation_ = transformation; }


private:
	ShaderProgram& shaderProgram_;
	Model& model_;

	std::shared_ptr<Transformation> transformation_ = nullptr;

};
