#pragma once
#include <map>
#include "ECS/Entity.h"

struct IScript;

class ScriptManager
{
public:
    ScriptManager();
    ~ScriptManager();
    
    template <typename SType, typename ... Args>
    SType* CreateScript(Entity* entity, Args&&... args);

    template <typename SType, typename ... Args>
    SType* CreatePersistentScript(Entity* entity, Args&&... args);

    template<typename S>
    S* GetScript(Entity* pEntity);
    
    void RemoveEntity(int* index);

    void OnCollisionEnter(Entity* collider, Entity* other);
    void OnTriggerEnter(Entity* collider, Entity* other);

    void OnCollisionStay(Entity* collider, Entity* other);
    void OnTriggerStay(Entity* collider, Entity* other);

    void OnCollisionExit(Entity* collider, Entity* other);
    void OnTriggerExit(Entity* collider, Entity* other);
    
    void OnRender(RenderWindow* window);
    
    void OnFixedUpdate();
    void OnUpdate();

private:
    std::map<int*, std::vector<IScript*>> scriptedEntity;
    std::map<int*, std::vector<IScript*>> scriptedEntityToAdd;
    std::vector<IScript*> persistentScript;
    int mEntityToRemoveCount;
    int** toRemoveId = new int*[1024];

    friend class GameManager;
};

#include "ScriptManager.inl"