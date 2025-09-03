#include "pch.h"
#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(Entity* entity, float lT)
    : Component(entity), Start(false), InProgress(false), MaxLifeTime(lT),
      LifeTime(0.0f) {}

ParticleEmitter::~ParticleEmitter()
{
}

int ParticleEmitter::GetBitmask()
{
    return BITMASK;
}
