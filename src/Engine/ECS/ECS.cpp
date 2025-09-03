#include "pch.h"
#include "ECS.h"

#include "Entity.h"
#include "Engine.h"
#include "Components/Component.h"
#include "Managers/GameManager.h"

#include "scripts/ScriptManager.h"
#include "Systems/CameraSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/ParticleSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/UserInterfaceSystem.h"
#include "Systems/AnimatorSystem.h"

ECS::ECS(): mEntityCount(0), mEntityToAddCount(0), mEntityToRemoveCount(0)
{
}

ECS::~ECS()
{
    for (int i = 0; i < mEntityCount; i++)
    {
        for (Component* component : mEntities[i]->AttachedComponents)
        {
            delete component;
            component = nullptr;
        }
        mEntities[i]->AttachedComponents.clear();
        delete mEntities[i]->Entity;
        delete mEntities[i];
    }
    mEntityCount = 0;
    
    for (int i = 0; i < mEntityToAddCount; i++)
    {
        for (Component* component : mToAddEntities[i]->AttachedComponents)
        {
            delete component;
            component = nullptr;
        }
        mToAddEntities[i]->AttachedComponents.clear();
        delete mToAddEntities[i]->Entity;
        delete mEntities[i];
    }
    mEntityToAddCount = 0;
    
}

void ECS::FixedUpdate()
{
    if (!Engine::GetGameManager()->mpNextActiveScene)
    {
        Engine::GetScriptManager()->OnFixedUpdate();
        Engine::GetPhysicsSystem()->OnFixedUpdate(this);
        Engine::GetCollisionSystem()->OnFixedUpdate(this);
    }
}

void ECS::Update()
{

    mEntityToRemoveCount = 0;
    for (int i = 0; i < mEntityCount; i++)
    {
        Entity* entity = mEntities[i]->Entity;

        if (entity->IsDestroyed())
        {
            mToRemoveEntityIndex[mEntityToRemoveCount] = entity->GetIndex();
            mEntityToRemoveCount++;
            Engine::GetScriptManager()->RemoveEntity(entity->GetIndex());
        }
    }

    for (int i = 0; i < mEntityToAddCount; i++)
    {
        EC* toAddEC = mToAddEntities[i];
        
        mEntities[mEntityCount] = toAddEC ;
        toAddEC->Entity->Create(mEntityCount);
        mEntityCount++;

        int layer = toAddEC->Entity->GetLayer();

        if(!mEntitiesByLayer.contains(layer))
        {
            mEntitiesByLayer[layer] = new std::list<Entity*>;
        }
        mEntitiesByLayer[layer]->push_back(toAddEC->Entity);
    }
    mEntityToAddCount = 0;

    for (int i = 0; i < mEntityToRemoveCount; i++)
    {
        int indexRemoved = *mToRemoveEntityIndex[i];
        Entity* entity = mEntities[indexRemoved]->Entity;
        int layer = entity->GetLayer();

        if (indexRemoved == mEntityCount-1)
        {
            for (Component* component : mEntities[indexRemoved]->AttachedComponents)
            {
                delete component;
            }
            delete mEntities[indexRemoved];
            mEntitiesByLayer[layer]->remove(entity);
            mEntityCount--;
            continue;
        }

        for (Component* component : mEntities[indexRemoved]->AttachedComponents)
        {
            delete component;
        }
        delete entity;

        Engine::GetCollisionSystem()->RemoveEntity(entity);
        
        std::list<Entity*>* entitiesByLayer = mEntitiesByLayer[layer];
        if (entitiesByLayer)
            entitiesByLayer->remove(entity);

        if (mEntities[indexRemoved])
            delete mEntities[indexRemoved];
        mEntities[indexRemoved] = mEntities[mEntityCount-1];
        mEntities[indexRemoved]->Entity->SetIndex(indexRemoved);
        mEntityCount--;
        
    }

    Engine::GetScriptManager()->OnUpdate();
    Engine::GetCameraSystem()->Update(this);
}

void ECS::Draw()
{
    Engine::GetScriptManager()->OnRender(Engine::GetRenderWindow());
    Engine::GetRenderSystem()->Render(this);
    Engine::GetParticleSystem()->Render(this);
    Engine::GetUserInterface()->Render(this);
}

bool ECS::IsEnable(int index)
{
    if(index >= mEntityCount) return false;
    Entity* entity = mEntities[index]->Entity;
    return entity->IsEnable();
}
