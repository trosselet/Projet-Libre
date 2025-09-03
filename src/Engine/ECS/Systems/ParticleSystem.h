#pragma once

class ParticleSystem
{
public:
    ParticleSystem(RenderWindow* window);
    ~ParticleSystem() = default;
    
    void Render(ECS* globalEC);

private:
    RenderWindow* mWindow;
    
};
