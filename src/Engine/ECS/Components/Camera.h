﻿#pragma once
#include "Component.h"

class Camera : public Component
{
public:
    static constexpr int BITMASK = 1 << 3;
    
    Camera(Entity* entity, int display = 0);
    ~Camera() override;

    int DisplayScreen;
    float ZoomFactor = 1.0f;
    
    int GetBitmask() override;
};
