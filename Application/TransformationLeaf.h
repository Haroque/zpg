#pragma once
#include <glm/vec3.hpp>
#include "Transformation.h"

class TransformationLeaf : public Transformation
{
public:
	virtual glm::mat4 getMatrix() = 0;
	virtual void update() override {}
};

class Translate : public TransformationLeaf
{
private:
	glm::vec3 translation_;
public:
	Translate(const glm::vec3& translation) : translation_(translation) {}
	glm::mat4 getMatrix() override;
};

class Rotate : public TransformationLeaf
{
private:
	float angle_;
	glm::vec3 axis_;
	float speed_;
	int direction_ = 1; // 1 for clockwise, -1 for counter-clockwise

public:
	Rotate(float angle, const glm::vec3& axis, float speed = 0.0f) : angle_(angle), axis_(axis), speed_(speed) {}
	void update() override;
	glm::mat4 getMatrix() override;
	void setRotationDirection(int direction) override { direction_ = direction; }
};

class Scale : public TransformationLeaf
{
private:
	glm::vec3 scale_;

public:
	Scale(const glm::vec3& scale) : scale_(scale) {}
	glm::mat4 getMatrix() override;
};

