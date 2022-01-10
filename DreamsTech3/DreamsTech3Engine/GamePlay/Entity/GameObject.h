
#pragma once
#include <vector>
#include "../Component/Base/Component.h"


#include "Object.h"

class GameObject:public Object
{
public:


	void Update() override;
template<typename T> Component* AddComponent(T* component);
template<typename T> bool RemoveComponent(T component);
template<typename T> Component* GetComponent(T component);
template<typename T> GameObject* FindGameObjectWithType(T component);
template<typename T> GameObject* FindGameObject(char* objectName);

	GameObject(char* name);
	~GameObject();


private:
	std::vector<Component*> _components;


};
