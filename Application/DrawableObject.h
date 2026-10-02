#pragma once

#include <memory>

#include <glm/vec3.hpp>

#include "Model.h"

class ShaderProgram;


class DrawableObject
{
public:
	DrawableObject(ShaderProgram& shaderProgram, std::unique_ptr<Model> model);

	void update();
	void setRotationDirection(int direction);
	void setPosition(const glm::vec3& position);
	void draw();

	void setVisible(bool visible) { isVisible_ = visible; }
    bool isVisible() const { return isVisible_; }

private:
	ShaderProgram& shaderProgram_;
	std::unique_ptr<Model> model_;
	bool isVisible_ = true;
};
