#pragma once

#include "State.h"
#include "ECS/Entity.h"

class StateMachine 
{
public:
    StateMachine(Entity* owner);

    void SetState(State* newState, Entity* player);
    void UpdateState(Entity* player);
    std::string GetStateName();

private:
    State* mp_CurrentState;
    Entity* mp_Owner;
};