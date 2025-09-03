#include "pch.h"
#include "EntityStateScript.h"
#include "Transform.h"

#include "Engine.h"
#include "Managers/GameManager.h"
#include "ECS/Components/Animator.h"


EntityStateScript::EntityStateScript(Entity* player, State* state)
{
    mp_StateMachine = nullptr;
    mp_player = player;
    mp_startingState = state;
}

EntityStateScript::~EntityStateScript()
{
}

void EntityStateScript::OnStart()
{
    if (owner->GetComponent<Animator>())
    {
        mp_StateMachine = new StateMachine(owner);
        mp_StateMachine->SetState(mp_startingState, mp_player);
    }

    if (owner->GetTag() == Entity::Tag::PLAYER)
    {
        m_LastPosition = owner->GetTransform()->position;
    }


#ifdef _DEBUG
    playerStateText.setCharacterSize(12);
    playerStateText.setFillColor(sf::Color::White);
#endif // _DEBUG

}

void EntityStateScript::OnFixedUpdate()
{
}

void EntityStateScript::OnUpdate()
{
    if (!mp_StateMachine)
        return;

    mp_StateMachine->UpdateState(mp_player);

    playerStateText.setPosition(owner->GetTransform()->position);
    playerStateText.setString("State: " + mp_StateMachine->GetStateName());

    if (owner->GetTag() == Entity::Tag::PLAYER)
    {
        if (m_LastPosition != owner->GetTransform()->position)
        {
            if (mp_StateMachine->GetStateName() != "PlayerIsWalking")
            {
                mp_StateMachine->SetState(new PlayerIsWalking, mp_player);
            }
            m_LastPosition = owner->GetTransform()->position;
            m_SwapToIdleTimer = 0;
        }
        else
        {
            m_SwapToIdleTimer += Engine::GetDeltaTime();
            if (m_SwapToIdleTimer > 0.1f)
            {
                mp_StateMachine->SetState(new IdlePlayer, mp_player);
            }
        }
    }

    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
    {
        mp_StateMachine->SetState(new PlayerIsChopping, mp_player);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
    {
        mp_StateMachine->SetState(new PlayerIsMining, mp_player);
    }
}

void EntityStateScript::OnDisable()
{
}

void EntityStateScript::OnRender(RenderWindow* window)
{
}
