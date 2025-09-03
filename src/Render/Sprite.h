#pragma once

#include <SFML/Graphics/Sprite.hpp>

class Texture;

class Sprite : public sf::Sprite
{
public:
    Sprite(Texture& sprite);
    Sprite(Texture& sprite, sf::Vector2f scaleFactor, sf::Vector2i texUV, sf::Vector2i texSize);
    Sprite(sf::Sprite& sprite);
    ~Sprite() override = default;
    
    void SetAlpha(uint8_t alpha);
    
    Sprite* Cut(int x, int y, int width, int height);
};
