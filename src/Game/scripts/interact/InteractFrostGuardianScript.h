#pragma once

#include "scripts/InteractScript.h"
#include "ECS/Entity.h"
#include "scripts/EntityStateScript.h"

class InteractFrostGuardianScript : public InteractScript
{
public:
	InteractFrostGuardianScript(Entity* player, PlayerMovement* playerMovement, EntityStateScript* stateMachine, MusicScript* music);
	~InteractFrostGuardianScript() = default;

	void Interact() override;
	void UnInteract() override;

private:
	EntityStateScript* mp_StateMachine = nullptr;
};

