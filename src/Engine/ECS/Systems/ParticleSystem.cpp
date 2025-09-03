#include "pch.h"
#include "ParticleSystem.h"

#include "ECS/ECS.h"
#include "ECS/Components/ParticleEmitter.h"

ParticleSystem::ParticleSystem(RenderWindow* window) : mWindow(window) { }

void ParticleSystem::Render(ECS* globalEC)
{
    for (int i = 0; i < globalEC->mEntityCount; i++)
    {
        if (!globalEC->HasComponent<ParticleEmitter>(i)) continue;
        ParticleEmitter* particle = globalEC->GetComponent<ParticleEmitter>(i);
    }
}
