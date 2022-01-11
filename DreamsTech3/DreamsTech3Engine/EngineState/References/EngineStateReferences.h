#pragma once

#include <vector>
#include "../../GamePlay/Entity/GameObject.h"
#include "../../Enums/EngineModes.h"

class EngineStateReferences
{
public:
    static EngineStateReferences* getInstance()
    {
        if (_instance == nullptr)
            _instance = new EngineStateReferences();

        return _instance;
    }


    EngineStateReferences(EngineStateReferences const&) = delete;
    void operator=(EngineStateReferences const&) = delete;

    friend class EngineStateManager;

private:
    EngineStateReferences(): _selectedObject(NULL)
    {
    }


private:
    GameObject _selectedObject;
	std::vector<GameObject*> _sceneObjects;
    EngineModes _currentEngineMode;

    static EngineStateReferences    *_instance;







};



