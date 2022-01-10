#include "GameObject.h"
#include "../../EngineState/Manager/EngineStateManager.h"
GameObject::GameObject(char* name):Object(name)
{
	
}

GameObject::~GameObject()
{
	for (auto item: _components)
	{
		delete item;
	}
}



template <typename T>
Component* GameObject::AddComponent(T* component)
{
	_components.emplace_back(component);
	return component;
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



void GameObject::Update()
{
	for (auto t : _components)
	{
		if (t != nullptr)
			t->Update();
	}
}
