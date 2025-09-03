#include "pch.h"
#include "Traveler.h"

#include "Transform.h"

void Traveler::OnFixedUpdate()
{
    owner->GetTransform()->position += mDirection * 30.0f * FIXED_DT;
    Debug::Log(std::to_string(owner->GetTransform()->position.x));
    if (owner->GetTransform()->position.x-600 < mMapOffsetX.x) mDirection.x *= -1.0f;
    if (owner->GetTransform()->position.x+600 > mMapOffsetX.y) mDirection.x *= -1.0f;
    if (owner->GetTransform()->position.y-400 < mMapOffsetY.x) mDirection.y *= -1.0f;
    if (owner->GetTransform()->position.y+400 > mMapOffsetY.y) mDirection.y *= -1.0f;
}

void Traveler::SetMapOffset(sf::Vector2f MapOffsetX, sf::Vector2f MapOffsetY)
{
    mMapOffsetX = MapOffsetX;
    mMapOffsetY = MapOffsetY;
}
