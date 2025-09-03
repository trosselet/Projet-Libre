#pragma once
#include "Component.h"

class Texture;

class Tilemap : public Component
{
public:
    static constexpr int BITMASK = 1 << 14;
    Tilemap(Entity* entity, std::string pathToTilemap);
    ~Tilemap() override;

    sf::VertexArray VertexArray;
    sf::VertexArray PropsVertexArray;
    sf::Texture* TilemapTexture;
    int GetBitmask() override;
};
