#pragma once

class Maths
{
public:
    static constexpr float PI = 3.1415926535f;
    static [[nodiscard]] float RandomFloat(float min, float max);
    static [[nodiscard]] int RandomInt(int min, int max);
};
