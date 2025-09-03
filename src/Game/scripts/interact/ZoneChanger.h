#pragma once
#include "ZoneManager.h"
#include "Managers/GameManager.h"
#include "scripts/Script.h"

template<typename T>
class ZoneChanger : public IScript
{
    ZoneManager* mZoneChanger;
    float mDestinationX, mDestinationY;

public:
    bool enter = false;

public:
    ZoneChanger(ZoneManager* manager, float x, float y);
    void OnTriggerEnter(Entity* other) override;
};

template <typename T>
ZoneChanger<T>::ZoneChanger(ZoneManager* manager, float x, float y)
{
    mZoneChanger = manager;
    mDestinationX = x;
    mDestinationY = y;
}

template <typename T>
void ZoneChanger<T>::OnTriggerEnter(Entity* other)
{
    if(other->IsTag(Entity::Tag::PLAYER))
    {
        Debug::Log("Enter");
        enter = true;
        mZoneChanger->SetSpawn(mDestinationX, mDestinationY);
        Engine::GetGameManager()->LaunchScene<T>();
    }
}
