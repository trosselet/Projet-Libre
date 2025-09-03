#include "pch.h"
#include "ZoneManager.h"

#include "Transform.h"

ZoneManager::ZoneManager()
{
}

void ZoneManager::OnStart()
{
}

void ZoneManager::SetSpawn(float x, float y)
{
    mSpawnX = x;
    mSpawnY = y;
    
}

sf::Vector2f ZoneManager::GetPosition()
{
    return sf::Vector2f(mSpawnX, mSpawnY);
}
