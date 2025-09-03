#include "pch.h"
#include "Transform.h"
#include "ECS/Entity.h"

TRANSFORM::TRANSFORM(Entity* npEntity) : mDirty(false)
{
    Identity();
    
    mpParentEntity = npEntity;
    mChildEntities = { };

    if (mpParentEntity != nullptr)
    {
        TRANSFORM* transform = mpParentEntity->GetTransform();
        SetPosition(transform->position);
    }
    
}

void TRANSFORM::Identity()
{

    scale.x = 1.0f;
    scale.y = 1.0f;

    position.x = 0.0f;
    position.y = 0.0f;

    rotation = sf::Angle::Zero;
    
    up.x = 0.0f;
    up.y = 1.0f;

    right.x = 1.0f;
    right.y = 0.0f;
}

void TRANSFORM::SetPosition(float x, float y)
{
    position = sf::Vector2f(x, y);
    for (Entity* child : mChildEntities)
    {
        child->GetTransform()->SetPosition(position);
    }
    mDirty = true;
}

void TRANSFORM::SetPosition(sf::Vector2f pVec)
{
    position = pVec;
    for (Entity* child : mChildEntities)
    {
        child->GetTransform()->SetPosition(pVec);
    }
    mDirty = true;
}

void TRANSFORM::SetScale(sf::Vector2f pScale)
{
    scale = pScale;
    for (Entity* child : mChildEntities)
    {
        child->GetTransform()->SetScale(pScale);
    }
    mDirty = true;
}

void TRANSFORM::SetRotation(sf::Angle pRotation)
{
    rotation = pRotation;
    for (Entity* child : mChildEntities)
    {
        child->GetTransform()->SetRotation(pRotation);
    }
    
    mDirty = true;
}

void TRANSFORM::Rotate(float x, float y)
{
    mDirty = true;
    
}

void TRANSFORM::RotateYaw(float angle)
{
    Rotate(0.0f, angle);
}

void TRANSFORM::RotatePitch(float angle)
{
    Rotate(angle, 0.0f);
}

Entity* TRANSFORM::GetParent() const
{
    return mpParentEntity;
}

void TRANSFORM::AddChild(Entity* nEntity)
{
    mChildEntities.push_back(nEntity);
}