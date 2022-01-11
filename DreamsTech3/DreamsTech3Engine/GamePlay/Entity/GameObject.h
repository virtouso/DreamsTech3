
#pragma once
#include <vector>

#include "../Component/Base/Component.fwd.h"
#include "../../GamePlay/Component/Transform/Transform.h"

#include "Object.h"


class GameObject :public Object
{
public:


	void Update() override;
	Transform* GetTransform() const;

	void AddComponent(Component* component);
	template<typename T> bool RemoveComponent(T component);
	template<typename T> Component* GetComponent(T component);
	std::vector<Component*> GetComponents();

	template<typename T> GameObject* FindGameObjectWithType(T component);
	template<typename T> GameObject* FindGameObject(char* objectName);




	GameObject(char* name);
	~GameObject();


private:
	std::vector<Component*> _components;
	Transform* _transform;

};
