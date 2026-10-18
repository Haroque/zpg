#pragma once
#include <glm/glm.hpp>
#include "Subject.h"

void Subject::attach(Observer* observer)
{
	if(observer)
		observers_.push_back(observer);
}
void Subject::detach(Observer* observer)
{
	observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}
void Subject::notifyAll()
{
	for (auto* observer : observers_)
	{
		if (observer)
			observer->notify();
	}
}