#pragma once
#include "Scripts/Script.h"

class ZoneManager : public IScript
{
    float mSpawnX = 1000.0f;
    float mSpawnY = 540.0f;

public:
    ZoneManager();

    void OnStart() override;
    void SetSpawn(float x, float y);
    sf::Vector2f GetPosition();
};
