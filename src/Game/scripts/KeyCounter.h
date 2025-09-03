#pragma once
#include <SFML/Graphics.hpp>

#include "ECS/Components/ui/Image.h"
#include "ECS/Components/ui/Text.h"

class KeyCounter {
public:
    KeyCounter(const std::string& keyLabel, sf::Vector2f position, sf::Font* font);

    void update(float deltaTime, bool isPressed);

    void setEnable(bool state);
    void increment();
    void reset();

private:
    Entity* background;
    Text* keyText;
    Text* kpsText;
    Text* counterText;
    std::vector<float> pressTimestamps;

    int count = 0;
    float alpha = 0.f;
    bool fadingIn = false;

    const float fadeSpeed = 300.f; 
    bool wasPressedLastFrame = false;

    sf::Clock beatClock;
};
