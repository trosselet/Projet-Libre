#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>

class Colors
{
public:
    static constexpr sf::Color blue = {0, 30, 100, 1};
    static constexpr sf::Color transparent_gray = {125, 125, 125, 100};
    static constexpr sf::Color transparent_green = {0, 125, 0, 100};
    static constexpr sf::Color green = { 191, 197, 15, 255 };
    static constexpr sf::Color transparent = { 191, 197, 15, 0 };
};
