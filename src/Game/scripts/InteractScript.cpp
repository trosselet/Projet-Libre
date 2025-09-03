#include "pch.h"
#include "InteractScript.h"
#include "MusicScript.h"
#include "ECS/Components/Collider2D.h"

InteractScript::InteractScript(Entity* player, PlayerMovement* playerMovement, MusicScript* music) : mp_player(player), mp_playerMovement(playerMovement), musicscript(music)
{
}

InteractScript::~InteractScript()
{
}

void InteractScript::OnStart()
{
}

void InteractScript::OnFixedUpdate()
{
}

void InteractScript::OnUpdate()
{
	if (owner->GetComponent<Collider2D>()->Intersects(mp_player->GetComponent<Collider2D>()).hasCollision)
	{
		m_CanInteract = true;
	}
	else
	{
		m_CanInteract = false;
	}

	if (!m_IsInteracting && m_CanInteract && GetKeyDown(Keyboard::Key::F))
	{
		m_IsInteracting = true;
		mp_playerMovement->SetCanMove(false);
		Interact();
	}
	else if (m_IsInteracting && GetKeyDown(Keyboard::Key::F) && musicscript->GetState() == MusicScript::MUSICSTATE::STOPPED)
	{
		m_IsInteracting = false;
		mp_playerMovement->SetCanMove(true);
		UnInteract();
	}
}

void InteractScript::OnDisable()
{
}

void InteractScript::OnRender(RenderWindow* window)
{
}
