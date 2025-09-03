#include "pch.h"
#include "ResourceInteraction.h"

#include "scripts/MusicScript.h"

ResourceInteraction::ResourceInteraction(Entity* player, PlayerMovement* playerMovement, MusicScript* music,
    Inventory* inventory, LootTable lootTable, int audioBeatmap)
    : InteractScript(player, playerMovement, music), mCanInteract(false), mIsStarted(false)
{
    mInventory = inventory;
    mLootTable = lootTable;
    mMusic = music;
    mBeatmap = audioBeatmap;
}

void ResourceInteraction::Interact()
{
    if (!mIsStarted)
    {
        // TODO : Mettre le nombre en dynamique
        mMusic->PlayBeatmap(mBeatmap);
        mIsStarted = true;
    }
}

void ResourceInteraction::UnInteract()
{
}

void ResourceInteraction::OnUpdate()
{
    if (mIsStarted && mMusic->GetState() == MusicScript::MUSICSTATE::STOPPED)
    {
        MusicScript::PlayerData data = mMusic->GetData();
        Item lastItem = mInventory->Items[mLootTable.Material];
        
        for (auto& recipeOut : mLootTable.Table)
        {
            if (data.Accuracy/100.0f >= recipeOut.first)
            {
                lastItem.actualCount = recipeOut.second;
            }
        }
        if (lastItem.type == ITEM)
            mInventory->AddItemCount(lastItem.id, lastItem.actualCount);
        mIsStarted = false;
        
        m_IsInteracting = false;
        mp_playerMovement->SetCanMove(true);
        
        owner->Destroy();
    }

    InteractScript::OnUpdate();
}
