#include "pch.h"
#include "PauseMenu.h"

#include "ObjectFactory.h"
#include "ECS/Components/ui/Button.h"
#include "ECS/Components/ui/Image.h"
#include "Managers/GameManager.h"
#include "scenes/finals/MainMenu.h"

void PauseMenu::OnStart()
{
    mPauseMenu = ObjectFactory::CreateEntity<Entity>(5);
    ObjectFactory::CreateComponent<Image>(mPauseMenu, Resources::instance().INVENTORY, Resources::instance().BLUR_SHADER, sf::Vector2f(1280, 600), sf::Vector2f(3.0f, 3.0f));
    ObjectFactory::CreateComponent<Text>(mPauseMenu, Resources::instance().DEFAULT_FONT, 15,
        "Jeu en pause", sf::Vector2f(1415, 620));
    
    Entity* resumeButton = ObjectFactory::CreateEntity<Entity>(mPauseMenu, 6);
    Button* resume = ObjectFactory::CreateComponent<Button>(resumeButton, Resources::instance().BUTTON,
        sf::Vector2f(1395, 720), 100, 20, [this] {
                Engine::GetClock()->SetTimeScale(1.0f);
                mPauseMenu->SetEnabled(false);
           }, [this] {
               
           });
    ObjectFactory::CreateComponent<Text>(resumeButton, Resources::instance().DEFAULT_FONT, 15,
        "Reprendre", sf::Vector2f(1395 + 25.0f, 720 + 5.0f));

    Entity* pauseButton = ObjectFactory::CreateEntity<Entity>(mPauseMenu, 6);
    Button* button = ObjectFactory::CreateComponent<Button>(pauseButton, Resources::instance().BUTTON,
        sf::Vector2f(1395, 820), 100, 20, [this] {
            Engine::GetGameManager()->LaunchScene<MainMenu>();
           }, [this] {
               
           });
    ObjectFactory::CreateComponent<Text>(pauseButton, Resources::instance().DEFAULT_FONT, 15,
        "Quitter le jeu", sf::Vector2f(1395 + 15.0f, 820 + 5.0f));

    button->Scale = {3.0f, 3.0f};
    resume->Scale = {3.0f, 3.0f};
    mPauseMenu->SetEnabled(false);
}

void PauseMenu::OnUpdate()
{

    if(GetKeyDown(Keyboard::Escape))
    {
        bool isPaused = !mPauseMenu->IsEnable();
        mPauseMenu->SetEnabled(isPaused);
        if (isPaused)
        {
            Engine::GetClock()->SetTimeScale(0.0f);
        } else
        {
            Engine::GetClock()->SetTimeScale(1.0f);
        }
    }

}
