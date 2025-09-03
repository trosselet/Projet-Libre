#include "pch.h"
#include "InteractGrolux.h"

InteractGrolux::InteractGrolux(Entity* player, PlayerMovement* playerMovement, EntityStateScript* stateMachine, MusicScript* music) : InteractScript(player, playerMovement, music)
{
	mp_StateMachine = stateMachine;
}

void InteractGrolux::Interact()
{
	mp_StateMachine->GetOwnerStateMachine()->SetState(new GroluxIsAttacking, mp_player);
	mp_playerMovement->SetCanMove(true);
}

void InteractGrolux::UnInteract()
{
}
