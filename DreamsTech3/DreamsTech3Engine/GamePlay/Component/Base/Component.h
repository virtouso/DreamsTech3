#pragma once
#include <string>

class Component
{
public:
	virtual std::string GetName() = 0;
	virtual void Update() = 0;
	virtual ~Component() = 0;
};
