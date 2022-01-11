#pragma once

class GameObject;

class EngineStateManager
{
public:
    static EngineStateManager* getInstance()
    {
        if (_instance == nullptr)
            _instance = new EngineStateManager();

        return _instance;
    }



    GameObject* FindGameObject(char* objectName);
    void AddObjectToScene(GameObject* gameObject);
    void RunUpdateAllSceneObjects();
public:
    GameObject* GetSelectedObject() const;
    void SetSelectedObject(const GameObject& gameObject);



   void ChangeEngineMode();


private:
    EngineStateManager() {}
    static EngineStateManager*    _instance;

public:
    EngineStateManager(EngineStateManager const&) = delete;
    void operator=(EngineStateManager const&) = delete;


};
