#include "pch.h"
#include "Light.h"

Light::Light(Entity* entity, sf::Color color, float strength) :
Component(entity), Color(color), Strength(strength)
{
    
}


int Light::GetBitmask()
{
    return BITMASK;
}
