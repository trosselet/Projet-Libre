#pragma once
#include "scripts/InteractScript.h"
#include "scripts/Inventory.h"

class MusicScript;

struct LootTable
{
    Material Material;
    std::map<float, int> Table;
};

class ResourceInteraction : public InteractScript
{

    Inventory* mInventory;
    MusicScript* mMusic;
    LootTable mLootTable;
    int mBeatmap;
    bool mCanInteract;
    bool mIsStarted;
    
public:
    ResourceInteraction(Entity* player, PlayerMovement* playerMovement, MusicScript* music, Inventory* inventory, LootTable lootTable, int audioBeatmap);

    void Interact() override;
    void UnInteract() override;
    void OnUpdate() override;
};
