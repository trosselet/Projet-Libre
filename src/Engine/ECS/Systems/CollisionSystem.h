#pragma once
#include <set>
#include <unordered_set>

#include "ECS/Components/Collider2D.h"

class ECS;

struct CollisionPair
{
    Collider2D* col1;
    Collider2D* col2;

    CollisionPair(Collider2D* c1, Collider2D* c2)
    {
        if (c1 < c2) { 
            col1 = c1; 
            col2 = c2; 
        } else { 
            col1 = c2; 
            col2 = c1; 
        }
    }

    bool operator==(const CollisionPair& other) const
    {
        return col1 == other.col1 && col2 == other.col2;
    }
};

struct CollisionPairHash {
    std::size_t operator()(const CollisionPair& pair) const {
        return std::hash<Collider2D*>()(pair.col1) ^ std::hash<Collider2D*>()(pair.col2);
    }
};

class CollisionSystem
{
    float mFixedTimestep = 1.0f / 60.0f;
public:
    CollisionSystem();
    static CollisionSystem& Get();
    void OnFixedUpdate(ECS* globalEC);
    void HandleOnEvents();
    void DetectCollisions(ECS* globalEC);
    void ProcessCollision(Collider2D* collider1, Collider2D* collider2);
    void UpdateColliders(ECS* globalEC);
    void ResolvePositions();
    void ResolveVelocities();
    void UpdateManifolds();
    void RemoveEntity(Entity* entity);
    bool HasManifold(Collider2D* col1, Collider2D* col2);
private:
    std::vector<CollisionManifold> mManifoldList = {};
    std::unordered_set<CollisionPair, CollisionPairHash> mPreviousCollisions = {};
    std::unordered_set<CollisionPair, CollisionPairHash> mCurrentCollisions = {};
    
    SpatialGrid* mGrid;
    std::vector<Entity*> mNeighboringEntities;
    
    std::set<Entity*> mRemovedEntities;

    friend GameManager;
};
