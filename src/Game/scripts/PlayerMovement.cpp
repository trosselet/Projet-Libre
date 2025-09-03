#include "pch.h"
#include "PlayerMovement.h"

#include "Transform.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"

PlayerMovement::PlayerMovement(Camera* camera) : mTransform(nullptr),
                                                 linkedCamera(camera->GetEntity()->GetTransform())
{
}

void PlayerMovement::OnStart()
{
    mTransform = owner->GetTransform();
}

void PlayerMovement::OnFixedUpdate()
{
    m_speed = 350.0f;
    sf::Vector2f playerPosition = mTransform->position + movement * m_speed * FIXED_DT;
    mTransform->SetPosition(playerPosition);
    movement = sf::Vector2f(0, 0);
    Debug::Log("x "+ std::to_string(mTransform->position.x) + " / y " + std::to_string(mTransform->position.y));
}

void PlayerMovement::OnCollisionEnter(Entity* other)
{
    std::cout << "Collision Enter" << std::endl;
}

void PlayerMovement::OnUpdate()
{
    if (m_CanMove)
    {
        if (Keyboard::GetKey(Keyboard::Key::D))
        {
            movement.x = mTransform->right.x;
        }
        if (Keyboard::GetKey(Keyboard::Key::Q))
        {
            movement.x = -mTransform->right.x;
        }
        if (Keyboard::GetKey(Keyboard::Key::S))
        {
            movement.y = mTransform->up.y;
        }
        if (Keyboard::GetKey(Keyboard::Key::Z))
        {
            movement.y = -mTransform->up.y;
        }
    }

    sf::Vector2f cameraPosition = mTransform->position;
    cameraPosition.x = std::clamp(cameraPosition.x, mSizeX.x, mSizeX.y);
    cameraPosition.y = std::clamp(cameraPosition.y, mSizeY.x, mSizeY.y);
    linkedCamera->position = cameraPosition - sf::Vector2f(960, 540);
}


void PlayerMovement::OnDisable()
{
    
}

void PlayerMovement::SetCanMove(bool canMove)
{
    m_CanMove = canMove;
}

void PlayerMovement::SetMapOffset(sf::Vector2f sizeX, sf::Vector2f sizeY)
{
    mSizeX = sizeX;
    mSizeY = sizeY; 
}
