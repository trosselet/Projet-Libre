#pragma once
#include "Component.h"

class Light : public Component
{
public:
    Light(Entity* entity, sf::Color color, float strength);
    
    sf::Color Color;
    float Strength;
    
    static constexpr int BITMASK = 1 << 6;
    int GetBitmask() override;
};
