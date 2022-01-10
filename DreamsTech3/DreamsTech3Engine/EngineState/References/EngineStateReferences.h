#pragma once

#include <vector>
#include "../../GamePlay/Entity/GameObject.h"
#include "../../Enums/EngineModes.h"

class EngineStateReferences
{
public:
    static EngineStateReferences& getInstance()
    {
        static EngineStateReferences    instance;

        return instance;
    }



private:
	std::vector<GameObject*> _sceneObjects;
    EngineModes _currentEngineMode;

private:
    EngineStateReferences() {}


public:
    EngineStateReferences(EngineStateReferences const&) = delete;
    void operator=(EngineStateReferences const&) = delete;

    friend class EngineStateManager;
};



