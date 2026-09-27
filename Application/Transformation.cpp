#include "Transformation.h"

#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation()
    : model_(1.0f),
      view_(glm::lookAt(
          glm::vec3(0.0f, 0.0f, 3.0f), // eye
          glm::vec3(0.0f, 0.0f, 0.0f),    // center
          glm::vec3(0.0f, 1.0f, 0.0f)     // nahoru
      )),
      projection_(glm::perspective(
          glm::radians(45.0f),            // Zorný úhel 
          800.0f / 600.0f,                    //    acspect ratio
          0.01f,                          // near plane
          100.0f                          //   far plane
      ))
{
}

void Transformation::update()
{
	rotationAngle_ += rotationDirection_ * 0.01f;
	model_ = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.5f, 0.0f));
	model_ = glm::rotate(model_, rotationAngle_, glm::vec3(0.0f, 0.0f, 1.0f));
	model_ = glm::translate(model_, glm::vec3(0.5f, 0.5f, 0.0f));
}

void Transformation::setRotationDirection(float direction)
{
	rotationDirection_ = direction;
}

const glm::mat4& Transformation::model() const { return model_; }
const glm::mat4& Transformation::view() const { return view_; }
const glm::mat4& Transformation::projection() const { return projection_; }