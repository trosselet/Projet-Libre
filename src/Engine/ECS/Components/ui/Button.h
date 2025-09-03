#pragma once
#include <functional>

#include "ECS/Components/Component.h"

class Sprite;

class Button : public Component
{
public:
    static constexpr int BITMASK = 1 << 17;
    
    Button(Entity* entity, Sprite* uiImage = nullptr, sf::Vector2f position = {0.0f, 0.0f}, int width = 50, int height = 50, std::function<void()> buttonAction = nullptr, std::function<void()> releaseAction = nullptr);
    ~Button() override = default;
    int GetBitmask() override;

    Sprite* UIImage;
    sf::Vector2f ScreenPosition;
    sf::Vector2f Scale = {1.0, 1.0};
    int Width;
    int Height;

    bool IsClicked;
    bool IsReleased;

    sf::RectangleShape* shape;

   std::function<void()> CallBack;
   std::function<void()> ReleaseCallback;
};
