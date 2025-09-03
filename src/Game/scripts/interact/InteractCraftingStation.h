#pragma once
#include "scripts/InteractScript.h"
#include "scripts/resources/Craft.h"

class InteractCraftingStation final : public InteractScript
{
    Craft* mCraftingStation;
public:
    InteractCraftingStation(Entity* player, PlayerMovement* playerMovement, Craft* craftStation, MusicScript* music);
    void Interact() override;
    void UnInteract() override;
    
};
