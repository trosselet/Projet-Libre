#include "pch.h"
#include "Forest.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Animator.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Tilemap.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "scripts/Inventory.h"
#include "ECS/Components/ui/Button.h"
#include "Managers/GameManager.h"
#include "ECS/Components/Animator.h"
#include "scripts/EntityFactory.h"
#include "scripts/interact/InteractCraftingStation.h"
#include "scripts/interact/ResourceInteraction.h"
#include "scripts/resources/Craft.h"
#include "scripts/tilemap/TilemapEditor.h"
#include "scripts/StatistiqueScript.h"
#include "scripts/EntityStateScript.h"
#include "scripts/interact/ZoneManager.h"
#include "TransitionVillageForest.h"
#include <scripts/interact/ZoneChanger.h>
#include "scripts/interact/InteractGrolux.h"

#include "scripts/QuestScript.h"
#include "scripts/menus/PauseMenu.h"

void Forest::OnEnter()
{
    
    Entity* cameraContainer = ObjectFactory::CreateEntity<Entity>();
    Camera* camera = ObjectFactory::CreateComponent<Camera>(cameraContainer);
    camera->ZoomFactor = 0.65f;
    
    Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Tilemap>(gridContainer, "../../res/Tiles/saved/forest.txt");

    Entity* player = ObjectFactory::CreateEntity<Entity>(50);
    ObjectFactory::AttachScript<PauseMenu>(player);

    ZoneManager* zoneManager = Engine::GetGameManager()->GetOrLoadGlobalScript<ZoneManager>(player);
    player->GetTransform()->SetPosition(1430, 1630);
    ObjectFactory::CreateComponent<AABBCollider>(player, -15.0f, -5.0f, 15.0f, 25.0f);
    Animator* pAnim = ObjectFactory::CreateComponent<Animator>(player, Resources::instance().PLAYER_IDLE, 0.1f);
    player->SetTag(Entity::Tag::PLAYER);

    StatistiqueScript* playerStat = ObjectFactory::AttachScript<StatistiqueScript>(player, 20, 10, 0, 300);
    ObjectFactory::AttachScript<EntityStateScript>(player, player, new IdlePlayer);

    bgm = ObjectFactory::AttachScript<BGMMusicScript>(player);

    bgm->AddMusic(1, "../../res/Music/BGM/beach_bgm.mp3");
    bgm->SetVolume(1);
    bgm->PlayBGMMusic(1);

    MusicScript* music = ObjectFactory::AttachScript<MusicScript>(player, bgm);
    

    music->AddBeatmap(1, "../../res/Beatmaps/5.txt", "../../res/Music/5.mp3", 191.95f, -60.f); // fingercontrol
    music->AddBeatmap(2, "../../res/Beatmaps/4.txt", "../../res/Music/4.ogg", 260.f, 40.f); // high bpm
    music->AddBeatmap(3, "../../res/Beatmaps/wood_beatmap.txt", "../../res/Music/wood.mp3", 260.f, 40.f); // high bpm
    music->AddBeatmap(4, "../../res/Beatmaps/8.txt", "../../res/Music/8.mp3", 222.f, -100.f);
    player->SetTag(Entity::Tag::PLAYER);
    
    PlayerMovement* movement = ObjectFactory::AttachScript<PlayerMovement>(player, camera);
    movement->SetMapOffset({630.0f, 2400.0f}, {360.0f, 1410.0f}); // DO NOT TOUCH
    
    Entity* canvas = ObjectFactory::CreateEntity<Entity>();
    Entity* invContainer = ObjectFactory::CreateEntity<Entity>(canvas);
    Inventory* inventory = Engine::GetGameManager()->GetOrLoadGlobalScript<Inventory>(player);
    
    LootTable treeTable = LootTable{ WOOD_DARK_OAK,
        {
                    {0.5f, 1},
                    {0.8f, 2},
                    {0.99f, 5}
        }
    };
    
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1065, 459, 100, 100, 3 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 905, 383, 100, 100, 3 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 655, 463, 100, 100, 3 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 483, 415, 100, 100, 3 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 415, 227, 100, 100, 3 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 575, 207, 100, 100, 3 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 685, 67, 100, 100, 3 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 945, 149, 100, 100, 3 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 775, 239, 100, 100, 3 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1095, 49, 100, 100, 3 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1205, 239, 100, 100, 3 );
    
    Entity* monster = ObjectFactory::CreateEntity<Entity>();
    monster->GetTransform()->SetPosition(100.0f, 100.0f);
    //ObjectFactory::CreateComponent<SpriteRenderer>(monster, Resources::instance().DEFAULT_MONSTER_SPRITE);
    ObjectFactory::CreateComponent<AABBCollider>(monster, 0.0f, 0.0f, 10.0f, 10.0f);
    monster->GetComponent<AABBCollider>()->SetTrigger(true);
    monster->SetTag(Entity::Tag::ENNEMY);
    inventory->zoom = camera->ZoomFactor;
    
    Entity* door = ObjectFactory::CreateEntity<Entity>();
    door->GetTransform()->SetPosition(1300, 1740);
    ObjectFactory::CreateComponent<SpriteRenderer>(door, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider = ObjectFactory::CreateComponent<AABBCollider>(door, 0, 0, 200, 25);
    doorCollider->SetTrigger(true);
    doorCollider->SetStatic(true);
    ObjectFactory::AttachScript<ZoneChanger<TransitionVillageForest>>(door, zoneManager, 540, 190);

    Entity* Grolux = ObjectFactory::CreateEntity<Entity>();
    Grolux->GetTransform()->SetPosition(2300.0f, 1300.0f);
    ObjectFactory::CreateComponent<Animator>(Grolux, Resources::instance().GROLUX_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(Grolux, -45.0f, -45.0f, 45.0f, 45.0f);
    Grolux->GetComponent<AABBCollider>()->SetTrigger(true);
    Grolux->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* GroluxStateMachine = ObjectFactory::AttachScript<EntityStateScript>(Grolux, player, new IdleGrolux);
    InteractGrolux* GroluxInteract = ObjectFactory::AttachScript<InteractGrolux>(Grolux, player, movement, GroluxStateMachine, music);


    quest = Engine::GetGameManager()->GetOrLoadGlobalScript<QuestScript>(player);
    quest->SetObjective(5, Engine::GetScriptManager()->GetScript<EntityStateScript>(Grolux)->IsDead());
}

void Forest::OnExit()
{
    bgm->StopBGMMusic();
    quest->RemoveObjective(5);
}
