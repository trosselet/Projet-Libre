#pragma once
#include "scripts/Script.h"
#include "state-machine/StateMachine.h"
#include "state-machine/State.h"


class EntityStateScript : public IScript
{
public:
	EntityStateScript(Entity* player, State* state);
	~EntityStateScript() override;

    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;
    void OnRender(RenderWindow* window) override;

    inline StateMachine* GetOwnerStateMachine() { return mp_StateMachine; };
    inline bool* IsDead() { return &m_isDead; };
    inline void SetIsDead(bool isDead) { m_isDead = isDead; };

private:
    sf::Text playerStateText = *Resources::instance().DEFAULT_FONT;
    StateMachine* mp_StateMachine;

private:
    Entity* mp_player;
    sf::Vector2f m_LastPosition;
    float m_SwapToIdleTimer = 0;
    State* mp_startingState;
    bool m_isDead = false;
};

