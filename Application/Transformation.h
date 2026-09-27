#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Transformation
{
public:
	Transformation();

	void update();
	void setRotationDirection(float direction);
	void setPosition(const glm::vec3& position);
	const glm::mat4& model() const;
	const glm::mat4& view() const;
	const glm::mat4& projection() const;

private:
	glm::mat4 model_;
	glm::mat4 view_;
	glm::mat4 projection_;
	glm::vec3 position_ = glm::vec3(0.0f);
	float rotationAngle_ = 0.0f;
	float rotationDirection_ = 0.0f;
};