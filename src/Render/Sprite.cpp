#include "Sprite.h"

#include "Texture.h"

Sprite::Sprite(Texture& texture) : sf::Sprite(texture)
{
}

Sprite::Sprite(Texture& texture, sf::Vector2f scaleFactor, sf::Vector2i texUV, sf::Vector2i texSize) : sf::Sprite(texture)
{
    setTextureRect(sf::IntRect(texUV, texSize));
    scale(scaleFactor);
}

Sprite::Sprite(sf::Sprite& sprite) : sf::Sprite(sprite)
{
}

void Sprite::SetAlpha(uint8_t alpha)
{
    sf::Color color = getColor();
    color.a = alpha;
    setColor(color);
}

Sprite* Sprite::Cut(int x, int y, int width, int height)
{
    Sprite* part = new Sprite(*this);
    part->setTextureRect(sf::IntRect({x,y}, {width,height}));
    part->scale({1.0f, 1.0f});
    return part;
}