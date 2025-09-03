#include "pch.h"
#include "AABBCollider.h"
#include "../Render/Colors.h"

AABBCollider::AABBCollider(Entity* entity, float xMin, float yMin, float xMax, float yMax) : Collider2D(entity)
{
    mColliderType = ColliderType::AABB;
    mXMax = xMax;
    mYMax = yMax;
    mXMin = xMin;
    mYMin = yMin;
    
}
