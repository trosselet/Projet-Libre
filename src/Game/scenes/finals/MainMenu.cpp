#include "pch.h"
#include "MainMenu.h"

#include "ECS/Components/Camera.h"
#include "ECS/Entity.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Village.h"
#include "ECS/Components/Tilemap.h"
#include "ECS/Components/ui/Button.h"
#include "ECS/Components/ui/Image.h"
#include "ECS/Components/ui/Text.h"
#include "Managers/GameManager.h"
#include "scripts/EntityFactory.h"
#include "scripts/menus/Traveler.h"
#include "scripts/BGMMusicScript.h"

#include <chrono>

#include "scripts/QuestScript.h"

void MainMenu::OnEnter()
{
    Entity* cameraContainer = ObjectFactory::CreateEntity<Entity>();
    cameraContainer->GetTransform()->SetPosition(600, 400);
    Camera* camera = ObjectFactory::CreateComponent<Camera>(cameraContainer);
    camera->ZoomFactor = 1.0f;

    QuestScript* quest = Engine::GetGameManager()->GetOrLoadGlobalScript<QuestScript>(nullptr);
    quest->SetState(true);

    BGMMusicScript* bgm = ObjectFactory::AttachScript<BGMMusicScript>(cameraContainer);
    bgm->AddMusic(1, "../../res/Music/BGM/menu_bgm.mp3");
    bgm->SetVolume(5);
    bgm->PlayBGMMusic(1);

    Traveler* traveler = ObjectFactory::AttachScript<Traveler>(cameraContainer);
    traveler->SetMapOffset({ -610.0f, 1500.0f }, { -350.0f, 980.0f });

    loadingScreen = ObjectFactory::CreateEntity<Entity>(5);
    ObjectFactory::CreateComponent<Image>(loadingScreen, Resources::instance().RESOURCE_BACKGROUND,
        Resources::instance().BLUR_SHADER, sf::Vector2f(-100, -100), sf::Vector2f(4.0f, 3.0f));
    loadingText = ObjectFactory::CreateComponent<Text>(
        loadingScreen,
        Resources::instance().DEFAULT_FONT,
        48,
        "Loading.",
        sf::Vector2f(850, 500)
    );

    loadStart = std::chrono::steady_clock::now();
}

void MainMenu::OnUpdate()
{
    if (menuLoaded)
        return;

    auto now = std::chrono::steady_clock::now();
    float elapsed = std::chrono::duration<float>(now - loadStart).count();

    int dotCount = static_cast<int>(elapsed) % 4;
    
    loadingText->WriteText->setString("Loading" + std::string(dotCount, '.'));
    if (elapsed >= 1.55)
    {
        if (loadingScreen)
            loadingScreen->Destroy();

        // === Load Main Menu Content ===

        Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
        ObjectFactory::CreateComponent<Tilemap>(gridContainer, "../../res/Tiles/saved/village.txt");

        Entity* mPauseMenu = ObjectFactory::CreateEntity<Entity>(5);
        ObjectFactory::CreateComponent<Image>(mPauseMenu, Resources::instance().INVENTORY,
            Resources::instance().BLUR_SHADER, sf::Vector2f(700, 350), sf::Vector2f(4.0f, 3.0f));
        ObjectFactory::CreateComponent<Text>(mPauseMenu, Resources::instance().DEFAULT_FONT, 36,
            "BEAT'N'HIT", sf::Vector2f(875, 380));

        Entity* resumeButton = ObjectFactory::CreateEntity<Entity>(mPauseMenu, 6);
        Button* resume = ObjectFactory::CreateComponent<Button>(resumeButton, Resources::instance().BUTTON,
            sf::Vector2f(850, 470), 200, 40, [this] {
                Engine::GetGameManager()->LaunchScene<Village>();
                Engine::GetClock()->SetTimeScale(1.0f);
            }, [this] {});
        ObjectFactory::CreateComponent<Text>(resumeButton, Resources::instance().DEFAULT_FONT, 24,
            "Jouer au jeu", sf::Vector2f(890, 483));
        resume->Scale = { 4.0f, 4.0f };

        Entity* pauseButton = ObjectFactory::CreateEntity<Entity>(mPauseMenu, 6);
        Button* button = ObjectFactory::CreateComponent<Button>(pauseButton, Resources::instance().BUTTON,
            sf::Vector2f(850, 580), 200, 40, [this] {
                Engine::GetGameManager()->Stop();
            }, [this] {});
        ObjectFactory::CreateComponent<Text>(pauseButton, Resources::instance().DEFAULT_FONT, 24,
            "Quitter le jeu", sf::Vector2f(890, 593));
        button->Scale = { 4.0f, 4.0f };

        // Add buildings
        EntityFactory::CreateBuilding(900, 400, Resources::instance().RESOURCE_BUILDING_BLUE2);
        EntityFactory::CreateBuilding(1130, 430, Resources::instance().RESOURCE_BUILDING_GREEN);
        EntityFactory::CreateBuilding(900, 730, Resources::instance().RESOURCE_BUILDING_GREEN2);
        EntityFactory::CreateBuilding(1130, 760, Resources::instance().RESOURCE_BUILDING_BLUE);
        EntityFactory::CreateBuilding(300, 430, Resources::instance().RESOURCE_BUILDING_BLUE);
        EntityFactory::CreateBuilding(530, 400, Resources::instance().RESOURCE_BUILDING_GREEN2);
        EntityFactory::CreateBuilding(205, 700, Resources::instance().RESOURCE_BUILDING_SHOP);
        EntityFactory::CreateBuilding(200, 940, Resources::instance().RESOURCE_BUILDING_MEDIC);

        menuLoaded = true;
    }
}

