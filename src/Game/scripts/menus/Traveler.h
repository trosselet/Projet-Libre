#pragma once
#include "scripts/Script.h"

class Traveler : public IScript
{
    sf::Vector2f mMapOffsetX = {0, 0};
    sf::Vector2f mMapOffsetY = {0, 0};
    sf::Vector2f mDirection = {1, 1};
    
public:
    void OnFixedUpdate() override;
    void SetMapOffset(sf::Vector2f MapOffsetX, sf::Vector2f MapOffsetY);
    
};
