#include "pch.h"
#include "State.h"
#include "ECS/Components/Animator.h"

#include "Transform.h"
#include "Engine/Managers/GameManager.h"
#include "scripts/EntityFactory.h"

#include "scripts/PlayerMovement.h"
#include "scripts/MusicScript.h"
#include "scripts/BGMMusicScript.h"
#include "scripts/Inventory.h"
#include "scripts/interact/ResourceInteraction.h"
#include "scripts/EntityStateScript.h"

/*================================== Player ===================================*/
void IdlePlayer::Start(Entity* owner, Entity* player)
{
    owner->GetComponent<Animator>()->SetAnimation(Resources::instance().PLAYER_IDLE, 0.1f);
}

void IdlePlayer::Update(Entity* owner, Entity* player)
{
}

void IdlePlayer::End(Entity* owner, Entity* player)
{
}

std::string IdlePlayer::GetStateName()
{
    return "PlayerIdle";
}

void PlayerIsMining::Start(Entity* owner, Entity* player)
{
}

void PlayerIsMining::Update(Entity* owner, Entity* player)
{
}

void PlayerIsMining::End(Entity* owner, Entity* player)
{
}

std::string PlayerIsMining::GetStateName()
{
    return "PlayerIsMining";
}

void PlayerIsChopping::Start(Entity* owner, Entity* player)
{
}

void PlayerIsChopping::Update(Entity* owner, Entity* player)
{
}

void PlayerIsChopping::End(Entity* owner, Entity* player)
{
}

std::string PlayerIsChopping::GetStateName()
{
    return "PlayerIsChopping";
}

void PlayerIsWalking::Start(Entity* owner, Entity* player)
{
    owner->GetComponent<Animator>()->SetAnimation(Resources::instance().PLAYER_WALK, 0.1f);
}

void PlayerIsWalking::Update(Entity* owner, Entity* player)
{
}

void PlayerIsWalking::End(Entity* owner, Entity* player)
{
}

std::string PlayerIsWalking::GetStateName()
{
    return "PlayerIsWalking";
}

void PlayerIsAttacking::Start(Entity* owner, Entity* player)
{
}

void PlayerIsAttacking::Update(Entity* owner, Entity* player)
{
}

void PlayerIsAttacking::End(Entity* owner, Entity* player)
{
}

std::string PlayerIsAttacking::GetStateName()
{
    return "PlayerIsAttacking";
}

/*================================= Monster ===================================*/

void IdleEyeBall::Start(Entity* owner, Entity* player)
{
    owner->GetComponent<Animator>()->SetAnimation(Resources::instance().EVIL_EYE_IDLE, 0.1f);
}

void IdleEyeBall::Update(Entity* owner, Entity* player)
{
}

void IdleEyeBall::End(Entity* owner, Entity* player)
{
}

std::string IdleEyeBall::GetStateName()
{
    return "EyeBallIdle";
}


void EyeBallIsAttacking::Start(Entity* owner, Entity* player)
{
    owner->GetComponent<Animator>()->SetAnimation(Resources::instance().EVIL_EYE_ATTACK, 0.1f);
}

void EyeBallIsAttacking::Update(Entity* owner, Entity* player)
{

    MusicScript* mMusic = Engine::GetScriptManager()->GetScript<MusicScript>(player);

    sf::Vector2f position = owner->GetTransform()->position;
    sf::Vector2f playerPosition = player->GetTransform()->position;
    sf::Vector2f direction = sf::Vector2f(playerPosition.x - position.x, playerPosition.y - position.y);

    if (m_timeUntilMusic < m_timeToMusic && !m_isInFight)
    {


        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (magnitude != 0)
        {
            direction.x /= magnitude;
            direction.y /= magnitude;

        }
        else
        {
            return;
        }

        int x = playerPosition.x - position.x;
        int y = playerPosition.y - position.y;

        float distance = std::sqrt(x * x + y * y);

        if (distance <= 0.0f)
        {
            owner->GetTransform()->SetPosition(playerPosition);
            direction = sf::Vector2f(0, 0);
        }

        float dt = Engine::GetDeltaTime();
        float speed = 350;
        float newDistance = dt * 50;
        sf::Vector2f translation = newDistance * direction;

        sf::Vector2f goToPosition = position + translation * speed * FIXED_DT;
        owner->GetTransform()->SetPosition(goToPosition);
    }
    else if (m_timeUntilMusic >= m_timeToMusic && !m_isInFight)
    {
        m_isInFight = true;

        LootTable evilEyeTable = LootTable{ IRON,
            {
                {0.5f, 2},
                {0.8f, 5},
                {0.99f, 20}
            }
        };

        Inventory* inventory = Engine::GetGameManager()->GetOrLoadGlobalScript<Inventory>(player);

        EntityFactory::CreateResource(mMusic, player, Engine::GetScriptManager()->GetScript<PlayerMovement>(player), inventory, evilEyeTable, position.x, position.y, 100, 100, 3);

        owner->GetComponent<Animator>()->SetAnimation(Resources::instance().EVIL_EYE_IDLE, 0.1f);
    }

    if (mMusic->GetState() == MusicScript::MUSICSTATE::PLAYING)
    {
        m_isMusicPlaying = true;
        Engine::GetScriptManager()->GetScript<BGMMusicScript>(player)->PauseBGMMusic(true);
    }

    if (mMusic->GetState() == MusicScript::MUSICSTATE::STOPPED && m_isMusicPlaying)
    {
        Engine::GetScriptManager()->GetScript<BGMMusicScript>(player)->PauseBGMMusic(false);

        Engine::GetScriptManager()->GetScript<EntityStateScript>(owner)->GetOwnerStateMachine()->SetState(new EyeBallIsDead, player);
    }

    m_timeUntilMusic += Engine::GetDeltaTime();
}

void EyeBallIsAttacking::End(Entity* owner, Entity* player)
{
}

std::string EyeBallIsAttacking::GetStateName()
{
    return "EyeBallIsAttacking";
}

void EyeBallIsDead::Start(Entity* owner, Entity* player)
{
    Engine::GetScriptManager()->GetScript<EntityStateScript>(owner)->SetIsDead(true);
}

void EyeBallIsDead::Update(Entity* owner, Entity* player)
{
    owner->Destroy();
}

void EyeBallIsDead::End(Entity* owner, Entity* player)
{
}

std::string EyeBallIsDead::GetStateName()
{
    return "EyeBallIsDead";
}


void IdleFrostGuardian::Start(Entity* owner, Entity* player)
{
    owner->GetComponent<Animator>()->SetAnimation(Resources::instance().FROST_GUARDIAN_IDLE, 0.1f);
}

void IdleFrostGuardian::Update(Entity* owner, Entity* player)
{

}

void IdleFrostGuardian::End(Entity* owner, Entity* player)
{
}

std::string IdleFrostGuardian::GetStateName()
{
    return "GuardianIdle";
}

void FrostGuardianIsAttacking::Start(Entity* owner, Entity* player)
{
    owner->GetComponent<Animator>()->SetAnimation(Resources::instance().FROST_GUARDIAN_ATTACK, 0.1f);
}

void FrostGuardianIsAttacking::Update(Entity* owner, Entity* player)
{
    MusicScript* mMusic = Engine::GetScriptManager()->GetScript<MusicScript>(player);

    sf::Vector2f position = owner->GetTransform()->position;
    sf::Vector2f playerPosition = player->GetTransform()->position;
    sf::Vector2f direction = sf::Vector2f(playerPosition.x - position.x, playerPosition.y - position.y);

    if (m_timeUntilMusic < m_timeToMusic && !m_isInFight)
    {


        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (magnitude != 0)
        {
            direction.x /= magnitude;
            direction.y /= magnitude;

        }
        else
        {
            return;
        }

        int x = playerPosition.x - position.x;
        int y = playerPosition.y - position.y;

        float distance = std::sqrt(x * x + y * y);

        if (distance <= 0.0f)
        {
            owner->GetTransform()->SetPosition(playerPosition);
            direction = sf::Vector2f(0, 0);
        }

        float dt = Engine::GetDeltaTime();
        float speed = 350;
        float newDistance = dt * 50;
        sf::Vector2f translation = newDistance * direction;

        sf::Vector2f goToPosition = position + translation * speed * FIXED_DT;
        owner->GetTransform()->SetPosition(goToPosition);
    }
    else if (m_timeUntilMusic >= m_timeToMusic && !m_isInFight)
    {
        m_isInFight = true;

        LootTable frostGuardianTable = LootTable{ IRON,
            {
                {0.5f, 2},
                {0.8f, 5},
                {0.99f, 20}
            }
        };

        Inventory* inventory = Engine::GetGameManager()->GetOrLoadGlobalScript<Inventory>(player);

        EntityFactory::CreateResource(mMusic, player, Engine::GetScriptManager()->GetScript<PlayerMovement>(player), inventory, frostGuardianTable, position.x, position.y, 100, 100, 3);
        
        owner->GetComponent<Animator>()->SetAnimation(Resources::instance().FROST_GUARDIAN_IDLE, 0.1f);
    }

    if (mMusic->GetState() == MusicScript::MUSICSTATE::PLAYING)
    {
        m_isMusicPlaying = true;
        Engine::GetScriptManager()->GetScript<BGMMusicScript>(player)->PauseBGMMusic(true);
    }

    if (mMusic->GetState() == MusicScript::MUSICSTATE::STOPPED && m_isMusicPlaying)
    {
        Engine::GetScriptManager()->GetScript<BGMMusicScript>(player)->PauseBGMMusic(false);


        Engine::GetScriptManager()->GetScript<EntityStateScript>(owner)->GetOwnerStateMachine()->SetState(new FrostGuardianIsDead, player);
    }

    m_timeUntilMusic += Engine::GetDeltaTime();
}

void FrostGuardianIsAttacking::End(Entity* owner, Entity* player)
{
}

std::string FrostGuardianIsAttacking::GetStateName()
{
    return "GuardianIsAttacking";
}

void FrostGuardianIsDead::Start(Entity* owner, Entity* player)
{
    Engine::GetScriptManager()->GetScript<EntityStateScript>(owner)->SetIsDead(true);
}

void FrostGuardianIsDead::Update(Entity* owner, Entity* player)
{
    owner->Destroy();
}

void FrostGuardianIsDead::End(Entity* owner, Entity* player)
{
}

std::string FrostGuardianIsDead::GetStateName()
{
    return "FrostGuardianIsDead";
}

void IdleGrolux::Start(Entity* owner, Entity* player)
{
    owner->GetComponent<Animator>()->SetAnimation(Resources::instance().GROLUX_IDLE, 0.1f);
}

void IdleGrolux::Update(Entity* owner, Entity* player)
{
}

void IdleGrolux::End(Entity* owner, Entity* player)
{
}

std::string IdleGrolux::GetStateName()
{
    return "GroluxIsIdle";
}

void GroluxIsAttacking::Start(Entity* owner, Entity* player)
{
    owner->GetComponent<Animator>()->SetAnimation(Resources::instance().GROLUX_ATTACK, 0.1f);
}

void GroluxIsAttacking::Update(Entity* owner, Entity* player)
{
    MusicScript* mMusic = Engine::GetScriptManager()->GetScript<MusicScript>(player);

    sf::Vector2f position = owner->GetTransform()->position;
    sf::Vector2f playerPosition = player->GetTransform()->position;
    sf::Vector2f direction = sf::Vector2f(playerPosition.x - position.x, playerPosition.y - position.y);

    if (m_timeUntilMusic < m_timeToMusic && !m_isInFight)
    {


        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (magnitude != 0)
        {
            direction.x /= magnitude;
            direction.y /= magnitude;

        }
        else
        {
            return;
        }

        int x = playerPosition.x - position.x;
        int y = playerPosition.y - position.y;

        float distance = std::sqrt(x * x + y * y);

        if (distance <= 0.0f)
        {
            owner->GetTransform()->SetPosition(playerPosition);
            direction = sf::Vector2f(0, 0);
        }

        float dt = Engine::GetDeltaTime();
        float speed = 350;
        float newDistance = dt * 50;
        sf::Vector2f translation = newDistance * direction;

        sf::Vector2f goToPosition = position + translation * speed * FIXED_DT;
        owner->GetTransform()->SetPosition(goToPosition);
    }
    else if (m_timeUntilMusic >= m_timeToMusic && !m_isInFight)
    {
        m_isInFight = true;

        LootTable groluxTable = LootTable{ STEEL,
            {
                {0.5f, 1},
                {0.8f, 2},
                {0.99f, 5}
            }
        };

        Inventory* inventory = Engine::GetGameManager()->GetOrLoadGlobalScript<Inventory>(player);

        EntityFactory::CreateResource(mMusic, player, Engine::GetScriptManager()->GetScript<PlayerMovement>(player), inventory, groluxTable, position.x, position.y, 100, 100, 2);

        owner->GetComponent<Animator>()->SetAnimation(Resources::instance().GROLUX_IDLE, 0.1f);
    }

    if (mMusic->GetState() == MusicScript::MUSICSTATE::PLAYING)
    {
        m_isMusicPlaying = true;
        Engine::GetScriptManager()->GetScript<BGMMusicScript>(player)->PauseBGMMusic(true);
    }

    if (mMusic->GetState() == MusicScript::MUSICSTATE::STOPPED && m_isMusicPlaying)
    {
        Engine::GetScriptManager()->GetScript<BGMMusicScript>(player)->PauseBGMMusic(false);

        Engine::GetScriptManager()->GetScript<EntityStateScript>(owner)->GetOwnerStateMachine()->SetState(new GroluxIsDead, player);
    }

    m_timeUntilMusic += Engine::GetDeltaTime();
}

void GroluxIsAttacking::End(Entity* owner, Entity* player)
{
}

std::string GroluxIsAttacking::GetStateName()
{
    return "GroluxIsAttacking";
}

void GroluxIsDead::Start(Entity* owner, Entity* player)
{
    Engine::GetScriptManager()->GetScript<EntityStateScript>(owner)->SetIsDead(true);
}

void GroluxIsDead::Update(Entity* owner, Entity* player)
{
    owner->Destroy();
}

void GroluxIsDead::End(Entity* owner, Entity* player)
{
}

std::string GroluxIsDead::GetStateName()
{
    return "GroluxIsDead";
}

void NPCIdle::Start(Entity* owner, Entity* player)
{
}

void NPCIdle::Update(Entity* owner, Entity* player)
{
}

void NPCIdle::End(Entity* owner, Entity* player)
{
}

std::string NPCIdle::GetStateName()
{
    return "NPCIdle";
}

void NPCTalking::Start(Entity* owner, Entity* player)
{
}

void NPCTalking::Update(Entity* owner, Entity* player)
{
}

void NPCTalking::End(Entity* owner, Entity* player)
{
}

std::string NPCTalking::GetStateName()
{
    return "NPCIsTalking";
}


