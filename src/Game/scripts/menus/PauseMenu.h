#pragma once
#include "scripts/Inventory.h"
#include "scripts/Script.h"

class PauseMenu : public IScript
{
    Entity* mPauseMenu = nullptr;

public:
    void OnStart() override;

    void OnUpdate() override;

    
};
