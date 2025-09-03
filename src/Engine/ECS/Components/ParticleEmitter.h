#pragma once

#include "Component.h"

struct ParticleEmitter : public Component
{
    ParticleEmitter(Entity* entity, float lT = 1.0f);
    ~ParticleEmitter();
    
    bool Start;
    bool InProgress;
    float MaxLifeTime;
    float LifeTime;
    
    static constexpr int BITMASK = 1 << 5;
    
    int GetBitmask() override;
    
};
