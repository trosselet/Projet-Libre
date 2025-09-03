#include "pch.h"
#include "RigidBody2D.h"

RigidBody2D::RigidBody2D(Entity* entity, bool UsingGravity, float nMass, float nDamping, RIGIDBODYTYPE nType) :
    Component(entity), IsStatic(false)
{
    mVelocity = {0.0f, 0.0f};
    mMass = nMass;
    mGravity = -9.81f;
    UseGravity = UsingGravity;
    mDamping = nDamping;

    mType = nType;
}

void RigidBody2D::SetType(RIGIDBODYTYPE nType)
{
    mType = nType;
}

void RigidBody2D::SetMass(float nMass)
{
    mMass = nMass;
}


void RigidBody2D::AddForce(sf::Vector2f force)
{
    mAllForces += force;
}

void RigidBody2D::SubtractForce(sf::Vector2f force)
{
    mAllForces -=force;
}

void RigidBody2D::AddForce(float x, float y)
{
    mAllForces.x += x;
    mAllForces.y += y;
}


sf::Vector2f RigidBody2D::GetForce() const
{
    return mAllForces;
}

void RigidBody2D::ClearForces()
{
    mAllForces = {0.0f,0.0f};
}

int RigidBody2D::GetBitmask()
{
    return BITMASK;
}

void RigidBody2D::ClearVelocity()
{
    mVelocity.x = 0.0f;
    mVelocity.y = 0.0f;
}

void RigidBody2D::ApplyImpulse(sf::Vector2f impulse)
{
    if (IsStatic || mMass == 0) return;
    
    mVelocity += impulse * GetInvMass() ;
}
