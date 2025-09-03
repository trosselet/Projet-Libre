#include "pch.h"
#include "Image.h"

Image::Image(Entity* entity, Sprite* uiImage, sf::Vector2f position, sf::Vector2f scale )
    : Component(entity), ScreenPosition(position), Scale(scale), UIImage(uiImage), UIShader(nullptr)
{
}

Image::Image(Entity* entity, Sprite* uiImage, Shader* shader, sf::Vector2f position, sf::Vector2f scale)
: Component(entity), ScreenPosition(position), Scale(scale), UIImage(uiImage), UIShader(shader)
{
}

int Image::GetBitmask()
{
    return BITMASK;
}
