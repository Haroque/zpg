#include "Transformation.h"

#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation()
    : model_(1.0f),
      view_(glm::lookAt(
          glm::vec3(0.0f, 0.0f, 3.0f), // eye
          glm::vec3(0.0f, 0.0f, 0.0f),    // center
          glm::vec3(0.0f, 1.0f, 0.0f)     // upper
      )),
      projection_(glm::perspective(
          glm::radians(45.0f),            // Zorný úhel 
          800.0f / 600.0f,                    //    aspect ratio
          0.01f,                          
          100.0f                          
      ))
{
}

void Transformation::update()
{
	rotationAngle_ += rotationDirection_ * 0.01f;
    model_ = glm::translate(glm::mat4(1.0f), position_);
	model_ = glm::rotate(model_, rotationAngle_, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Transformation::setRotationDirection(float direction)
{
	rotationDirection_ = direction;
}

void Transformation::setPosition(const glm::vec3& position)
{
    position_ = position;
    model_ = glm::translate(glm::mat4(1.0f), position_);
}

const glm::mat4& Transformation::model() const { return model_; }
const glm::mat4& Transformation::view() const { return view_; }
const glm::mat4& Transformation::projection() const { return projection_; }