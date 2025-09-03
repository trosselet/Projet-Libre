#pragma once

#include "Scene.h"
#include "scripts/ScriptManager.h"
#include "../Engine.h"
#include "scripts/Script.h"

template <typename T>
void GameManager::LaunchScene()
{
    static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");

    if (mpActiveScene)
    {
        mpNextActiveScene = new T();
        return;
    }

    T* newScene = new T();
    mpActiveScene = newScene;

    //INIT DE LA SCENE
    mpActiveScene->OnEnter();
    
}

template <typename S, typename ... Args>
S* GameManager::GetOrLoadGlobalScript(Entity* owner, Args&&... args)
{
    static_assert(std::is_base_of<IScript, S>::value, "S must be derived from IScript");

    for (int i = 0; i < dataHandler.size(); i++)
    {
        if (S* script = dynamic_cast<S*>(dataHandler[i]); script != nullptr)
        {
            script->owner = owner;
            script->OnStart();
            return script;
        }
    }

    S* script = Engine::GetScriptManager()->CreatePersistentScript<S>(owner, args...);
    dataHandler.push_back(script);

    return script;
}
