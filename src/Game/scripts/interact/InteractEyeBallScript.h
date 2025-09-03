#pragma once

#include "scripts/InteractScript.h"
#include "ECS/Entity.h"
#include "scripts/EntityStateScript.h"

class InteractEyeBallScript : public InteractScript
{
public:
	InteractEyeBallScript(Entity* player, PlayerMovement* playerMovement, EntityStateScript* stateMachine, MusicScript* music);
	~InteractEyeBallScript() = default;

	void Interact() override;
	void UnInteract() override;

private:
	EntityStateScript* mp_StateMachine = nullptr;
};

