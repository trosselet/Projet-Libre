#pragma once
#include "ECS/Components/Animator.h"
#include "scripts/Script.h"
#include "tilemap/TilemapEditor.h"

class RigidBody2D;

class PlayerMovement : public IScript
{
    
public:
    PlayerMovement(Camera* linkedCamera);
    
    void OnStart() override;
    void OnFixedUpdate() override;
    void OnCollisionEnter(Entity* other) override;
    void OnUpdate() override;
    void OnDisable() override;

    void SetCanMove(bool canMove);
    void SetMapOffset(sf::Vector2f sizeX, sf::Vector2f sizeY);

public:
    float m_speed = 0;

private:
    TRANSFORM* mTransform;
    TRANSFORM* linkedCamera;
    sf::Vector2f movement;
    bool m_CanMove = true;

    sf::Vector2f mSizeX;
    sf::Vector2f mSizeY;
};
