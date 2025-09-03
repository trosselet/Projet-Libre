#pragma once

class Collider2D;

struct CollisionManifold
{
    Collider2D* collider1;
    Collider2D* collider2;
    bool hasCollision = false;
    sf::Vector2f collisionNormal;
    float penetrationDepth = 0;

    bool operator<(const CollisionManifold& otherManifold) const
    {
        return this->penetrationDepth < otherManifold.penetrationDepth;
    }
    
};
