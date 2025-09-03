#pragma once
#include "Managers/Scene.h"

class QuestScript;

class Beach : public Scene
{

    QuestScript* quest;
    void OnEnter() override;
    void OnExit() override;
};
