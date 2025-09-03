#include "pch.h"
#include "GameManager.h"

#include "GameTimer.h"
#include "ECS/ECS.h"
#include "ECS/Systems/CollisionSystem.h"
#include "Inputs/Inputs.h"
#include "Render/RenderWindow.h"
#include "scripts/ScriptManager.h"
#include "Utils/Debug.h"
#include "Utils/Profiler.h"
#include "Inputs/Keyboard.h"

GameManager::~GameManager()
{
}

GameManager::GameManager(): mpActiveScene(nullptr), mpNextActiveScene(nullptr),
                            mWindowWidth(0), mWindowHeight(0),
                            mAccumulator(0), IsStopped(false)
{
    mProfiler = new Profiler();
}

void GameManager::Run()
{

    Profiler globalProfiler;
    while(!IsStopped)
    {
        
        globalProfiler.NewTask("Global Inputs");
        HandleInput();
        globalProfiler.EndTask();

        globalProfiler.NewTask("Update Global");
        Update();
        globalProfiler.EndTask();

        globalProfiler.NewTask("Draw Global");
        Draw();
        globalProfiler.EndTask();

        if (mpNextActiveScene)
        {
            mpActiveScene->OnExit();
            delete mpActiveScene;

            mpActiveScene = mpNextActiveScene;
            mpNextActiveScene = nullptr;

            for (auto& scripted_entity : Engine::GetScriptManager()->scriptedEntity)
            {
                for (IScript* script : scripted_entity.second)
                {
                    if (script)
                        delete script;
                    script = nullptr;
                }
            }

            for (int i = 0; i < Engine::GetECS()->mEntityCount; i++)
            {
                EC* entity = Engine::GetECS()->mEntities[i];
                for (Component* component : entity->AttachedComponents)
                {
                    delete component;
                    component = nullptr;
                }
                
            }

            Engine::GetCollisionSystem()->mPreviousCollisions.clear();
            Engine::GetCollisionSystem()->mGrid->GetAllCells().clear();
            Engine::GetScriptManager()->scriptedEntity.clear();
            Engine::GetScriptManager()->mEntityToRemoveCount = 0;
            Engine::GetECS()->mEntityCount = 0;
            Engine::GetECS()->mEntitiesByLayer.clear();
            Engine::GetRenderWindow()->clear();

            mpActiveScene->OnEnter();
            
        }

    }

}

void GameManager::Stop()
{
    IsStopped = true;
}

void GameManager::HandleInput()
{

    while (const std::optional event = Engine::GetRenderWindow()->pollEvent())
    {
        if (event)
        {
            //mpActiveScene->OnEvent(event);
            if (event->is<sf::Event::Closed>())
            {
                IsStopped = true;
                Engine::GetRenderWindow()->close();
            }
        }
    }

    if (Engine::GetRenderWindow()->hasFocus()) {
        Inputs::UpdateKeyboard();
        Inputs::UpdateMouse();
    }
}


void GameManager::FixedUpdate()
{
    mpActiveScene->OnFixedUpdate();
    
    Engine::GetECS()->FixedUpdate();
    
}

void GameManager::Draw()
{

    Engine::GetRenderWindow()->BeginFrame();
    
    mProfiler->NewTask("Draw window");
    Engine::GetECS()->Draw();
    mProfiler->EndTask();

    Engine::GetRenderWindow()->EndFrame();
    
}

GameTimer* GameManager::GetTime()
{
    return &mTimer;
}

void GameManager::Update()
{
    const int MAX_PHYSICS_STEPS = 1;
    int steps = 0;
    
    mTimer.UpdateTime();
   /* Debug::Log("FPS " + std::to_string(mTimer.GetFPS()));
    Debug::Log("Entity count " + std::to_string(Engine::GetECS()->mEntityCount));*/

    mAccumulator += mTimer.GetDeltaTime();
    mProfiler->NewTask("Physics update");
    while(mAccumulator >= FIXED_DT && steps < MAX_PHYSICS_STEPS)
    {
        FixedUpdate();
        mAccumulator -= FIXED_DT;
        steps++;
    }
    if (steps == MAX_PHYSICS_STEPS)
    {
        mAccumulator = 0.0;
    }
    mProfiler->EndTask();

    mProfiler->NewTask("Update ECS");
    Engine::GetECS()->Update();
    mProfiler->EndTask();
    
    mProfiler->NewTask("Update scene");
    mpActiveScene->OnUpdate();
    mProfiler->EndTask();
}


