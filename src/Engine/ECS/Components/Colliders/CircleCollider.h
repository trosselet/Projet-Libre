#pragma once
#include "ECS/Components/Collider2D.h"

class CircleCollider : public Collider2D
{
public:
    CircleCollider(Entity* entity, int radius);
    void SetRadius(float radius) { mRadius = radius; }
    float GetRadius() const { return mRadius; }
    
private:
    float mRadius;
};
