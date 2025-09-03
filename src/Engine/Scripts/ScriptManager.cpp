#include "pch.h"
#include "ScriptManager.h"

#include "Script.h"
#include "ECS/Entity.h"

ScriptManager::ScriptManager() : mEntityToRemoveCount(0) {}

ScriptManager::~ScriptManager()
{
    scriptedEntity.clear();
    scriptedEntityToAdd.clear();
    for (IScript* persistent_script : persistentScript)
    {
        delete persistent_script;
        persistent_script = nullptr;
    }
    persistentScript.clear();
}

void ScriptManager::RemoveEntity(int* index)
{
    toRemoveId[mEntityToRemoveCount++] = index;
    for (IScript* script : scriptedEntity[index])
    {
        if (!script->isPersistent)
            script->OnDisable();
    }
}

void ScriptManager::OnCollisionEnter(Entity* collider, Entity* other)
{
    for (IScript* script : scriptedEntity[collider->GetIndex()])
    {
        script->OnCollisionEnter(other);
    }
    for (auto& script : persistentScript)
    {
        if (script->owner == collider)
            script->OnCollisionEnter(other);
    }
}

void ScriptManager::OnTriggerEnter(Entity* collider, Entity* other)
{
    for (IScript* script : scriptedEntity[collider->GetIndex()])
    {
        script->OnTriggerEnter(other);
    }
    for (auto& script : persistentScript)
    {
        if (script->owner == collider)
            script->OnTriggerEnter(other);
    }
}

void ScriptManager::OnCollisionStay(Entity* collider, Entity* other)
{
    for (IScript* script : scriptedEntity[collider->GetIndex()])
    {
        script->OnCollisionStay(other);
    }
    for (auto& script : persistentScript)
    {
        if (script->owner == collider)
            script->OnCollisionStay(other);
    }
}

void ScriptManager::OnTriggerStay(Entity* collider, Entity* other)
{
    for (IScript* script : scriptedEntity[collider->GetIndex()])
    {
        script->OnTriggerStay(other);
    }
    for (auto& script : persistentScript)
    {
        if (script->owner == collider)
            script->OnTriggerStay(other);
    }
}

void ScriptManager::OnCollisionExit(Entity* collider, Entity* other)
{
    for (IScript* script : scriptedEntity[collider->GetIndex()])
    {
        script->OnCollisionExit(other);
    }
    for (auto& script : persistentScript)
    {
        if (script->owner == collider)
            script->OnCollisionExit(other);
    }
}

void ScriptManager::OnTriggerExit(Entity* collider, Entity* other)
{
    for (IScript* script : scriptedEntity[collider->GetIndex()])
    {
        script->OnTriggerExit(other);
    }
    for (auto& script : persistentScript)
    {
        if (script->owner == collider)
            script->OnTriggerExit(other);
    }
}

void ScriptManager::OnRender(RenderWindow* window)
{
    for (auto& idScripts : scriptedEntity)
    {
        for (IScript* script : idScripts.second)
        {
            script->OnRender(window);
        }
    }
    for (auto& script : persistentScript)
    {
        script->OnRender(window);
    }
}

void ScriptManager::OnFixedUpdate()
{
    for (auto& idScripts : scriptedEntity)
    {
        for (IScript* script : idScripts.second)
        {
            if (script->owner->IsDestroyed()) continue;
            script->OnFixedUpdate();
        }
    }
    for (auto& script : persistentScript)
    {
        script->OnFixedUpdate();
    }
}

void ScriptManager::OnUpdate()
{
    
    for (auto& idScriptToAdd : scriptedEntityToAdd)
    {
        for (IScript* script : idScriptToAdd.second)
        {
            script->OnStart();
            scriptedEntity[idScriptToAdd.first].push_back(script);
        }
    }
    scriptedEntityToAdd.clear();

    for (int i = 0; i < mEntityToRemoveCount; i++)
    {
        int* indexToRemove = toRemoveId[i];
        for (IScript* script : scriptedEntity[indexToRemove])
        {
            delete script;
            script = nullptr;
        }
        scriptedEntity.erase(indexToRemove);
    }
    mEntityToRemoveCount = 0;
    
    for (auto& idScripts : scriptedEntity)
    {
        for (IScript* script : idScripts.second)
        {
            script->OnUpdate();
        }
    }

    for (auto& script : persistentScript)
    {
        script->OnUpdate();
    }
}
