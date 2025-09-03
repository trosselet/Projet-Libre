#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "Sprite.h"

class Sprite;

class SpriteSheet : public sf::Sprite
{
    std::vector<sf::Vector2i> sprites;
    sf::Vector2i m_size;
    sf::Vector2i m_totalSize;

public:
    SpriteSheet(Texture& sprite);

    void Extract(int startX, int startY, int singleWidth, int singleHeight, int width = 1, int height = 1, bool reverse = false);
    sf::Vector2i GetSpriteSheetPart(int index);
    void SetSpriteAt(sf::Vector2i offset);
    void SetSprite(int index);
    sf::Vector2i GetSize();
    sf::Vector2i GetTotalSize();
    int SpriteCount;
};