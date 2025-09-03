#include "pch.h"
#include "InteractCraftingStation.h"

InteractCraftingStation::InteractCraftingStation(Entity* player, PlayerMovement* playerMovement, Craft* craftStation, MusicScript* music) : InteractScript(player, playerMovement, music)
{
    mCraftingStation = craftStation;
    mp_playerMovement = playerMovement;
}

void InteractCraftingStation::Interact()
{
    mCraftingStation->ToggleState();
}

void InteractCraftingStation::UnInteract()
{
    mCraftingStation->ToggleState();
}