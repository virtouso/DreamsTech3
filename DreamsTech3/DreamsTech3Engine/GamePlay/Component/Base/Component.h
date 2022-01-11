#pragma once

#include <string>

#include "../../Entity/GameObject.fwd.h"

class Component
{
public:
	virtual std::string GetName() = 0;
	virtual void Update() = 0;
	 Component(GameObject& parentGameObject);

	virtual ~Component() = 0;

private:
	GameObject& _parentGameObject;

};
