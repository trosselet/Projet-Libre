#pragma once
#include "Managers/Scene.h"
#include "ECS/Entity.h"
#include <SFML/Graphics/Text.hpp>

class ThomasScene : public Scene
{
    void OnEnter() override;
    void OnUpdate() override;
};
