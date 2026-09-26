#include "Transformation.h"

#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation()
		: model_(1.0f),
			view_(glm::lookAt(glm::vec3(10.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
			projection_(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.01f, 100.0f))
{
}

const glm::mat4& Transformation::model() const { return model_; }
const glm::mat4& Transformation::view() const { return view_; }
const glm::mat4& Transformation::projection() const { return projection_; }
