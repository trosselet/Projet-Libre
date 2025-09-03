#include "pch.h"
#include "InteractEyeBallScript.h"
#include "scripts/state-machine/State.h"

InteractEyeBallScript::InteractEyeBallScript(Entity* player, PlayerMovement* playerMovement, EntityStateScript* stateMachine, MusicScript* music) : InteractScript(player, playerMovement, music)
{
	mp_StateMachine = stateMachine;
}

void InteractEyeBallScript::Interact()
{
	mp_StateMachine->GetOwnerStateMachine()->SetState(new EyeBallIsAttacking, mp_player);
	mp_playerMovement->SetCanMove(true);
}

void InteractEyeBallScript::UnInteract()
{
	/*if (!m_IsInteracting)
	{
		mp_StateMachine->GetOwnerStateMachine()->SetState(new IdleEyeBall, mp_player);
	}*/
}
