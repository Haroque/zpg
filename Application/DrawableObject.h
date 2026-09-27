#pragma once

#include <memory>

#include <glm/vec3.hpp>

#include "Model.h"
#include "Transformation.h"

class ShaderProgram;


class DrawableObject
{
public:
	DrawableObject(ShaderProgram& shaderProgram, std::unique_ptr<Model> model);

	void update();
	void setRotationDirection(float direction);
	void setPosition(const glm::vec3& position);
	void draw();

	void setVisible(bool visible) { isVisible_ = visible; }
    bool isVisible() const { return isVisible_; }

private:
	ShaderProgram& shaderProgram_;
	std::unique_ptr<Model> model_;
	Transformation transformation_;
	bool isVisible_ = true;
};
