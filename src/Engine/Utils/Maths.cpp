#include "pch.h"
#include "Maths.h"

float Maths::RandomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / (RAND_MAX / (max - min));
}

int Maths::RandomInt(int min, int max)
{
    return min + rand() % (( max + 1 ) - min);
}
