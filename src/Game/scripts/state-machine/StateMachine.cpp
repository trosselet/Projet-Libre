#include "pch.h"
#include "StateMachine.h"

#include <typeinfo>

StateMachine::StateMachine(Entity* owner) : mp_Owner(owner), mp_CurrentState(nullptr)
{

}

void StateMachine::SetState(State* newState, Entity* player)
{
	if (mp_CurrentState && typeid(*mp_CurrentState) == typeid(*newState))
	{
		return;
	}

	if (mp_CurrentState) 
	{
		mp_CurrentState->End(mp_Owner, player);
	}
	mp_CurrentState = newState;
	mp_CurrentState->Start(mp_Owner, player);
}

void StateMachine::UpdateState(Entity* player)
{
	if (mp_CurrentState)
	{
		mp_CurrentState->Update(mp_Owner, player);
	}
}

std::string StateMachine::GetStateName()
{
	return (mp_CurrentState ? mp_CurrentState->GetStateName() : "State none");
}
