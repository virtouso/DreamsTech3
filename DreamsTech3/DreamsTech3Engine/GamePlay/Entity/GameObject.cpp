#include "GameObject.h"

#include <iostream>

#include "../../EngineState/Manager/EngineStateManager.h"
#include "../Component/Base/Component.h"
#include "../../GamePlay/Component/Transform/Transform.h"
#include "../../GamePlay/Component/Base/Component.h"

GameObject::GameObject(char* name) :Object(name), _transform(new Transform(*this))
{
	
}

GameObject::~GameObject()
{
	delete _transform;
	for (auto item : _components)
	{
		delete item;
	}
}




void GameObject::AddComponent(Component* component)
{
	_components.emplace_back(component);

}



template <typename T>
Component* GameObject::GetComponent(T component)
{
	for (auto t : _components)
	{
		if (typeid(t) == typeid (component))
			return t;
	}
	return nullptr;
}

std::vector<Component*> GameObject::GetComponents()
{
	return _components;
}



template <typename T>
GameObject* GameObject::FindGameObject(char* objectName)
{
	return EngineStateManager::getInstance().FindGameObject(objectName);
}

template <typename T>
GameObject* GameObject::FindGameObjectWithType(T component)
{
	//todo
	throw "not implemented yet;";
}

template <typename T>
bool GameObject::RemoveComponent(T component)
{
	for (int i = 0; i < _components.size(); i++)
	{

		if (typeid(_components[i]) == typeid(component)) {
			_components.erase(_components.begin() + i);
			return true;
		}
	}
	return false;
}


Transform* GameObject::GetTransform() const
{
	return _transform;
}



void GameObject::Update()
{

	for (auto t : _components)
	{
		if (t != nullptr)
			t->Update();
	}
}
