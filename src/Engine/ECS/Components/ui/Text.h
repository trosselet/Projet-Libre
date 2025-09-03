#pragma once
#include "ECS/Components/Component.h"

class Text : public Component
{
public:
    static constexpr int BITMASK = 1 << 18;
    
    Text(Entity* entity, sf::Font* font, int size, std::string text, sf::Vector2f position);
    ~Text() override;
    int GetBitmask() override;

    sf::Vector2f ScreenPosition;
    
    sf::Text* WriteText;
};
