#pragma once

#include "scripts/InteractScript.h"
#include "ECS/Entity.h"
#include "scripts/EntityStateScript.h"

class InteractGrolux : public InteractScript
{

public:
	InteractGrolux(Entity* player, PlayerMovement* playerMovement, EntityStateScript* stateMachine, MusicScript* music);
	~InteractGrolux() = default;

	void Interact() override;
	void UnInteract() override;

private:
	EntityStateScript* mp_StateMachine = nullptr;
};

