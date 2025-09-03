#pragma once

#include "ECS/Entity.h"

class MusicScript;

class State
{
public:
    virtual ~State() = default;
    virtual void Start(Entity* owner, Entity* player) = 0;
    virtual void Update(Entity* owner, Entity* player) = 0;
    virtual void End(Entity* owner, Entity* player) = 0;
    virtual std::string GetStateName() = 0;

};

/*========================= PLAYER ===============================*/

class IdlePlayer : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

class PlayerIsMining : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};
class PlayerIsChopping : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

class PlayerIsWalking : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

class PlayerIsAttacking : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

/*========================= MONSTER ===============================*/

class IdleEyeBall : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

class EyeBallIsAttacking : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;

private:
    float m_timeUntilMusic = 0.f;
    float m_timeToMusic = 3.f;
    bool m_isInFight = false;
    bool m_isMusicPlaying = false;

};

class EyeBallIsDead : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

class IdleFrostGuardian : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

class FrostGuardianIsAttacking : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;

private:
    float m_timeUntilMusic = 0.f;
    float m_timeToMusic = 3.f;
    bool m_isInFight = false;
    bool m_isMusicPlaying = false;
};

class FrostGuardianIsDead : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

class IdleGrolux : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

class GroluxIsAttacking : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;

private:
    float m_timeUntilMusic = 0.f;
    float m_timeToMusic = 3.f;
    bool m_isInFight = false;
    bool m_isMusicPlaying = false;
};

class GroluxIsDead : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

/*========================= NPC ===============================*/

class NPCIdle : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};

class NPCTalking : public State
{
public:
    void Start(Entity* owner, Entity* player) override;
    void Update(Entity* owner, Entity* player) override;
    void End(Entity* owner, Entity* player) override;
    std::string GetStateName() override;
};