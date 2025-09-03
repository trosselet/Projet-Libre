#pragma once

#include "ECS/Entity.h"

const float Pi = 3.1415926535f;

struct TRANSFORM
{
private:
    bool mDirty;
    
    std::vector<Entity*> mChildEntities;
    Entity* mpParentEntity;
    
public:
    TRANSFORM(Entity* npEntity);
    sf::Vector2f up;
    sf::Vector2f right;

    sf::Angle rotation;
    sf::Vector2f scale;
    sf::Vector2f position;

    Entity* GetParent() const;
    void AddChild(Entity* nEntity);
    std::vector<Entity*> GetChildList() const {return mChildEntities; }

    void Identity();
    
    void SetPosition(float x, float y);
    
    void SetPosition(sf::Vector2f pVec);
    void SetScale(sf::Vector2f pScale);
    void SetRotation(sf::Angle pRotation);
    
    void Rotate(float x, float y);
    void RotatePitch(float angle);
    void RotateYaw(float angle);
};
