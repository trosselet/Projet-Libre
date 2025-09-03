#include "pch.h"
#include "Button.h"

#include "Render/Colors.h"

Button::Button(Entity* entity, Sprite* sprite, sf::Vector2f position, int width, int height, std::function<void()> buttonAction, std::function<void()> releaseAction):
    Component(entity),
    UIImage(sprite), CallBack(buttonAction), ReleaseCallback(releaseAction), ScreenPosition(position), Width(width), Height(height),
    IsClicked(false), IsReleased(true)
{
    shape = new sf::RectangleShape({static_cast<float>(width), static_cast<float>(height)});
    shape->setFillColor(Colors::transparent_gray);
}

int Button::GetBitmask()
{
    return BITMASK;
}
