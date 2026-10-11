#include <vector>
#include <memory>
#include "TransformationComposite.h"

void TransformationComposite::addTransformation(std::shared_ptr<Transformation> transformation)
{
	transformations_.push_back(transformation);
}

void TransformationComposite::update()
{
	for (auto& transformation : transformations_)
	{
		transformation->update();
	}
}

glm::mat4 TransformationComposite::getMatrix()
{
	glm::mat4 result(1.0f);
	for (const auto& transformation : transformations_)
	{
		result = result * transformation->getMatrix();
	}
	return result;
}

void TransformationComposite::setRotationDirection(int direction)
{
	for (auto& transformation : transformations_)
	{
		transformation->setRotationDirection(direction);
	}
}