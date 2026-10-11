#pragma once
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformationLeaf.h"


// --- Translate ---
glm::mat4 Translate::getMatrix() {
	return glm::translate(glm::mat4(1.0f), translation_);
}

// --- Rotate ---
glm::mat4 Rotate::getMatrix() {
	return glm::rotate(glm::mat4(1.0f), angle_, axis_);
}

void Rotate::update()
{
	angle_ += speed_ * direction_;
}

// --- Scale ---
glm::mat4 Scale::getMatrix()
{
	return glm::scale(glm::mat4(1.0f), scale_);
}
