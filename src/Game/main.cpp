#include "pch.h"
#include "main.h"

#include "Resources.h"
#include "Managers/GameManager.h"

#include "scenes/Editor.h"
#include "scenes/ThomasScene.h"
#include "scenes/finals/Beach.h"
#include "scenes/finals/Forest.h"
#include "scenes/finals/MainMenu.h"
#include "scenes/finals/Village.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

    srand(time(nullptr));

    Engine::CreateRender();

    Resources::instance().Initialize();
    Engine::GetGameManager()->LaunchScene<MainMenu>();
    Engine::GetGameManager()->Run();

    return 0;

}
