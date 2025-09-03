#include "pch.h"
#include "Text.h"

Text::Text(Entity* entity, sf::Font* font, int size, std::string text, sf::Vector2f position)
: Component(entity)
{
    WriteText = new sf::Text(*font);
    ScreenPosition = position;
    WriteText->setString(text);
    WriteText->setCharacterSize(size);
}

Text::~Text()
{
    if (WriteText)
        delete WriteText;
}

int Text::GetBitmask()
{
    return BITMASK;
}
