#pragma once

#include <glm/mat4x4.hpp>

class Transformation
{
public:
	Transformation();

	const glm::mat4& model() const;
	const glm::mat4& view() const;
	const glm::mat4& projection() const;

private:
	glm::mat4 model_;
	glm::mat4 view_;
	glm::mat4 projection_;
};

