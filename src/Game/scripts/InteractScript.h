#pragma once
#include "scripts/Script.h"
#include "ECS/Entity.h"
#include "scripts/PlayerMovement.h"
#include "scripts/MusicScript.h"

class InteractScript : public IScript
{
public:
	InteractScript(Entity* player, PlayerMovement* playerMovement, MusicScript* musicscript);
	~InteractScript();

    void OnStart() override;
    void OnFixedUpdate() override;
    void OnUpdate() override;
    void OnDisable() override;
    void OnRender(RenderWindow* window) override;

    virtual void Interact() = 0;
    virtual void UnInteract() = 0;

    bool* IsInteractingPointer() { return &m_IsInteracting; }

private:
    bool m_CanInteract = false;

protected:
    bool m_IsInteracting = false;
    Entity* mp_player;
    PlayerMovement* mp_playerMovement;
	MusicScript* musicscript;
};

