/*
 * Antonin Harok HAR0199
 *
 * File: Transformation.h
 * Description:  Header file for the Transformation class
 */
#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Transformation
{
public:
	virtual ~Transformation() = default;
	virtual glm::mat4 getMatrix() = 0;
	virtual void update() {}
};