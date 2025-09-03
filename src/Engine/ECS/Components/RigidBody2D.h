#pragma once
#include "Component.h"

class RigidBody2D : public Component
{
public:
    
    enum class RIGIDBODYTYPE : uint8_t
    {
        BOX,
        SPHERE,
        OBB,

        TYPE_COUNT
    };
    
    RigidBody2D(Entity* entity, bool UsingGravity = true, float nMass = 1.0f, float nDamping = 0.5f, RIGIDBODYTYPE nType = RIGIDBODYTYPE::TYPE_COUNT);
    
    static constexpr int BITMASK = 1 << 1;

#pragma region Values
    float mGravity;
    float mMass; //Weight in KG
    float mDamping;
    bool UseGravity;
    bool IsStatic;
    RIGIDBODYTYPE mType;
    sf::Vector2f mVelocity;
    
protected:
    sf::Vector2f mAllForces = {0.0f,0.0f};
#pragma endregion

#pragma region Functions
public:
    void SetType(RIGIDBODYTYPE nType);
    void SetSize(float w, float h);
    void SetMass(float nMass);
    
    void AddForce(sf::Vector2f force);
    void SubtractForce(sf::Vector2f force);
    void AddForce(float x, float y);
    sf::Vector2f GetForce() const;
    void ClearForces();
    int GetBitmask() override;
    void ClearVelocity();
    float GetInvMass() const { return 1/mMass; }
    void ApplyImpulse(sf::Vector2f impulse);
#pragma endregion

};
