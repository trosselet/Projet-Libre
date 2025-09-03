#pragma once
#include "Utils/Debug.h"

class RenderSystem
{
    
public:
    RenderSystem(RenderWindow* window);
    ~RenderSystem();
    void Render(ECS* globalEC);

private:
    RenderWindow* window;
    
};
