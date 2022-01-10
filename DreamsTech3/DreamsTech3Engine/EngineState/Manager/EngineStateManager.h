#pragma once

class GameObject;

class EngineStateManager
{
public:
    static EngineStateManager& getInstance()
    {
        static EngineStateManager    instance;

        return instance;
    }



    GameObject* FindGameObject(char* objectName);


   void ChangeEngineMode();


private:
    EngineStateManager() {}


public:
    EngineStateManager(EngineStateManager const&) = delete;
    void operator=(EngineStateManager const&) = delete;


};
