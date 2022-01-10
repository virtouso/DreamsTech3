#include  "EngineStateManager.h"
#include "../References/EngineStateReferences.h"
//#include "../../Enums/EngineModes.h"



GameObject* EngineStateManager::FindGameObject(char* objectName)
{
	for (auto item : EngineStateReferences::getInstance()._sceneObjects)
	{
		if ((strcmp(item->Name, objectName) == 0))
			return item;
	}

	return nullptr;
}




void EngineStateManager::ChangeEngineMode()
{
	EngineStateReferences::getInstance()._currentEngineMode =
		static_cast<EngineModes>(!static_cast<int>(EngineStateReferences::getInstance()._currentEngineMode));
}
