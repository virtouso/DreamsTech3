#include "Component.h"
#include "../../Entity/GameObject.h"



Component::Component(GameObject& parentGameObject): _parentGameObject(parentGameObject)
{
}

Component::~Component()
{
}


void Component::Update()
{
	
}
void Component::DisplayInspector()
{
	
}



