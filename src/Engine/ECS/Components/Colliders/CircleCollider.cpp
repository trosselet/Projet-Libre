#include "pch.h"
#include "CircleCollider.h"
#include "../Render/Colors.h"

CircleCollider::CircleCollider(Entity* entity, int radius) : Collider2D(entity)
{
    mColliderType = ColliderType::CIRCLE;
    mRadius = radius;
    
}
