#pragma once
#include <vector>
#include "Observer.h"

class Subject
{
private:
	std::vector<Observer*> observers_;
public:
	virtual ~Subject() = default;
	void attach(Observer* observer);
	void detach(Observer* observer);
	void notifyAll();
};

