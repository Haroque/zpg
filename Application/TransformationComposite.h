#pragma once
#include <vector>
#include <memory>
#include "Transformation.h"


class TransformationComposite : public Transformation
{
public:
	void addTransformation(std::shared_ptr<Transformation> transformation);
	glm::mat4 getMatrix() override;
	void update() override;

private:
	std::vector<std::shared_ptr<Transformation>> transformations_;
};

