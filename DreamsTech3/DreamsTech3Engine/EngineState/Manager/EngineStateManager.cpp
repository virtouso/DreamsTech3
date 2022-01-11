#include  "EngineStateManager.h"

#include <iostream>

#include "../References/EngineStateReferences.h"

 EngineStateManager* EngineStateManager:: _instance=nullptr;


GameObject* EngineStateManager::FindGameObject(char* objectName)
{
	for (auto item : EngineStateReferences::getInstance()->_sceneObjects)
	{
		if ((strcmp(item->Name, objectName) == 0))
			return item;
	}

	return nullptr;
}




void EngineStateManager::ChangeEngineMode()
{
	EngineStateReferences::getInstance()->_currentEngineMode =
		static_cast<EngineModes>(!static_cast<int>(EngineStateReferences::getInstance()->_currentEngineMode));
}


void EngineStateManager::AddObjectToScene(GameObject* gameObject)
{
	EngineStateReferences::getInstance()-> _sceneObjects.emplace_back(gameObject);
}


void EngineStateManager::RunUpdateAllSceneObjects()
{

	for (auto item: EngineStateReferences::getInstance()->_sceneObjects)
	{
		item->Update();
	}
}



GameObject* EngineStateManager::GetSelectedObject() const
{
	return &EngineStateReferences::getInstance()->_selectedObject;
}

void EngineStateManager::SetSelectedObject(const GameObject& gameObject)
{
	 EngineStateReferences::getInstance()->_selectedObject = gameObject;
}