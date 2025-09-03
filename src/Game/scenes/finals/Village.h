#pragma once
#include "Managers/Scene.h"

class BGMMusicScript;
class QuestScript;

class Village : public Scene
{
    BGMMusicScript* bgm;
    QuestScript* quest;

    void OnEnter() override;
    void OnExit() override;
};
