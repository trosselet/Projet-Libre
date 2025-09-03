#include "pch.h"
#include "KeyCounter.h"
#include <sstream>

#include "ECS/Entity.h"
#include "ObjectFactory.h"

KeyCounter::KeyCounter(const std::string& keyLabel, sf::Vector2f position, sf::Font* font)
{

    background = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Image>(background, Resources::instance().ITEMBOX, sf::Vector2f(position.x + 1300.f + 13.f, position.y), sf::Vector2f(3.0f, 3.0f));

    Entity* keyTextContainer = ObjectFactory::CreateEntity<Entity>(background);
    keyText = ObjectFactory::CreateComponent<Text>(keyTextContainer, font, 10, keyLabel, sf::Vector2f(position.x + 1300.f + 24.f, position.y));

    Entity* countTextContainer = ObjectFactory::CreateEntity<Entity>(background);
    counterText = ObjectFactory::CreateComponent<Text>(countTextContainer, font, 12, "0", sf::Vector2f(position.x + 1300.f + 25.f, position.y + 25.f));

    
    Entity* kpsTextContainer = ObjectFactory::CreateEntity<Entity>(background);
    kpsText = ObjectFactory::CreateComponent<Text>(kpsTextContainer, font, 10, "KPS 0", sf::Vector2f(position.x + 1300.f + 28.f, position.y + 48.f));

    background->SetEnabled(false);
}

void KeyCounter::update(float deltaTime, bool isPressed)
{
    float currentTime = beatClock.getElapsedTime().asSeconds();

    if (isPressed && !wasPressedLastFrame)
    {
        fadingIn = true;
        alpha = 150;
        increment();
        pressTimestamps.push_back(currentTime);
    }

    wasPressedLastFrame = isPressed;

    while (!pressTimestamps.empty() && currentTime - pressTimestamps.front() > 1.0f)
    {
        pressTimestamps.erase(pressTimestamps.begin());
    }

    std::stringstream ss;
    ss.precision(2);
    ss << std::fixed << "KPS: " << pressTimestamps.size();
    kpsText->WriteText->setString(ss.str());
}

void KeyCounter::setEnable(bool state)
{
    background->SetEnabled(state);
}

void KeyCounter::increment()
{
   count++;
   counterText->WriteText->setString(std::to_string(count));
}

void KeyCounter::reset()
{
    count = 0;
    counterText->WriteText->setString("0");
}
