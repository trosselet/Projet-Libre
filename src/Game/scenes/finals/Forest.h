#pragma once
#include "Managers/Scene.h"

class BGMMusicScript;
class QuestScript;

class Forest : public Scene
{
    BGMMusicScript* bgm ;
    QuestScript* quest;
    void OnEnter() override;
    void OnExit() override;
};
