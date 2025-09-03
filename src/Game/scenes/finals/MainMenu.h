#pragma once
#include <chrono>
#include "ECS/Entity.h"
#include "Managers/Scene.h"
#include "ECS/Components/ui/Text.h"


class MainMenu : public Scene {
public:
    void OnEnter() override;
    void OnUpdate() override;

private:
    bool menuLoaded = false;
    Entity* loadingScreen = nullptr;
    class Text* loadingText = nullptr;

    std::chrono::steady_clock::time_point loadStart;

};
