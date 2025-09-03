#include "pch.h"
#include "InteractFrostGuardianScript.h"

InteractFrostGuardianScript::InteractFrostGuardianScript(Entity* player, PlayerMovement* playerMovement, EntityStateScript* stateMachine, MusicScript* music) : InteractScript(player, playerMovement, music)
{
	mp_StateMachine = stateMachine;
}

void InteractFrostGuardianScript::Interact()
{
	mp_StateMachine->GetOwnerStateMachine()->SetState(new FrostGuardianIsAttacking, mp_player);
	mp_playerMovement->SetCanMove(true);
}

void InteractFrostGuardianScript::UnInteract()
{
}
