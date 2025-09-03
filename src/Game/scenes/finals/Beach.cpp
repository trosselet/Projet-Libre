#include "pch.h"
#include "Beach.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Tilemap.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/ui/Button.h"
#include "scripts/EntityFactory.h"
#include "scripts/interact/InteractCraftingStation.h"
#include "scripts/interact/ResourceInteraction.h"
#include "scripts/interact/ZoneChanger.h"
#include "scripts/resources/Craft.h"
#include "scripts/tilemap/TilemapEditor.h"
#include "TransitionBeachPlain.h"
#include "ECS/Components/Animator.h"
#include "scripts/EntityStateScript.h"
#include "scripts/ParticlesScript.h"
#include "scripts/QuestScript.h"
#include "scripts/StatistiqueScript.h"
#include "scripts/interact/InteractEyeBallScript.h"
#include "scripts/interact/ZoneManager.h"
#include "scripts/menus/PauseMenu.h"

class PlainScene;

void Beach::OnEnter()
{
    
    Entity* cameraContainer = ObjectFactory::CreateEntity<Entity>();
    Camera* camera = ObjectFactory::CreateComponent<Camera>(cameraContainer);
    camera->ZoomFactor = 0.65f;
    
    Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Tilemap>(gridContainer, "../../res/Tiles/saved/beach.txt");

    Entity* player = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::AttachScript<PauseMenu>(player);
    ZoneManager* zoneManager = Engine::GetGameManager()->GetOrLoadGlobalScript<ZoneManager>(player);

    player->GetTransform()->SetPosition(zoneManager->GetPosition());
    ObjectFactory::CreateComponent<AABBCollider>(player, -15.0f, -5.0f, 15.0f, 25.0f);
    Animator* pAnim = ObjectFactory::CreateComponent<Animator>(player, Resources::instance().PLAYER_IDLE, 0.1f);
    player->SetTag(Entity::Tag::PLAYER);

    StatistiqueScript* playerStat = ObjectFactory::AttachScript<StatistiqueScript>(player, 20, 10, 0, 300);
    ObjectFactory::AttachScript<EntityStateScript>(player, player, new IdlePlayer);

    ObjectFactory::AttachScript<ParticlesScript>(player, 20000);

    BGMMusicScript* bgm = ObjectFactory::AttachScript<BGMMusicScript>(player);

    bgm->AddMusic(1, "../../res/Music/BGM/beach_bgm.mp3");
    bgm->SetVolume(1);
    bgm->PlayBGMMusic(1);

    MusicScript* music = ObjectFactory::AttachScript<MusicScript>(player, bgm);

    music->AddBeatmap(1, "../../res/Beatmaps/5.txt", "../../res/Music/5.mp3", 191.95f, -60.f); // fingercontrol
    music->AddBeatmap(2, "../../res/Beatmaps/4.txt", "../../res/Music/4.ogg", 260.f, 40.f); // high bpm
    music->AddBeatmap(3, "../../res/Beatmaps/4.txt", "../../res/Music/4.ogg", 222.f, -100.f);
    music->AddBeatmap(4, "../../res/Beatmaps/wood_beatmap.txt", "../../res/Music/wood.mp3", 260.f, 40.f); // high bpm

    PlayerMovement* movement = ObjectFactory::AttachScript<PlayerMovement>(player, camera);
    movement->SetMapOffset({ 630.0f, 1027.0f}, { 580.0f, 1000.0f });  // DO NOT TOUCH
    
    Entity* canvas = ObjectFactory::CreateEntity<Entity>();
    Entity* invContainer = ObjectFactory::CreateEntity<Entity>(canvas);
    Inventory* inventory = Engine::GetGameManager()->GetOrLoadGlobalScript<Inventory>(invContainer);
    
    LootTable treeTable = LootTable{ WOOD_PALM,
        {
                {0.5f, 1},
                {0.8f, 2},
                {0.99f, 5}
        }
    };
    
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1005, 321, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1030, 578, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 270, 804, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 525, 547, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 690, 389, 100, 100, 4 );
    ResourceInteraction* interaction = EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 270, 550, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 490, 800, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 720, 804, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 910, 900, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 910, 1050, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 910, 1220, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1070, 1282, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1230, 1283, 100, 100, 4 );
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1230, 325, 100, 100, 4 );
    
    Entity* door = ObjectFactory::CreateEntity<Entity>();
    door->GetTransform()->SetPosition(-50, 550);
    ObjectFactory::CreateComponent<SpriteRenderer>(door, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider = ObjectFactory::CreateComponent<AABBCollider>(door, 0, 0, 100, 200);
    doorCollider->SetTrigger(true);
    ObjectFactory::AttachScript<ZoneChanger<TransitionBeachPlain>>(door, zoneManager, 1350, 385);
  
    inventory->zoom = camera->ZoomFactor;

    Entity* EvilEye1 = ObjectFactory::CreateEntity<Entity>();
    EvilEye1->GetTransform()->SetPosition(1104.0f, 492.0f);
    ObjectFactory::CreateComponent<Animator>(EvilEye1, Resources::instance().EVIL_EYE_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(EvilEye1, -15.0f, -15.0f, 15.0f, 15.0f);
    EvilEye1->GetComponent<AABBCollider>()->SetTrigger(true);
    EvilEye1->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* EvilEye1StateMachine = ObjectFactory::AttachScript<EntityStateScript>(EvilEye1, player, new IdleEyeBall);
    InteractEyeBallScript* EvilEye1Interact = ObjectFactory::AttachScript<InteractEyeBallScript>(EvilEye1, player, movement, EvilEye1StateMachine, music);

    Entity* EvilEye2 = ObjectFactory::CreateEntity<Entity>();
    EvilEye2->GetTransform()->SetPosition(901.0f, 453.0f);
    ObjectFactory::CreateComponent<Animator>(EvilEye2, Resources::instance().EVIL_EYE_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(EvilEye2, -15.0f, -15.0f, 15.0f, 15.0f);
    EvilEye2->GetComponent<AABBCollider>()->SetTrigger(true);
    EvilEye2->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* EvilEye2StateMachine = ObjectFactory::AttachScript<EntityStateScript>(EvilEye2, player, new IdleEyeBall);
    InteractEyeBallScript* EvilEye2Interact = ObjectFactory::AttachScript<InteractEyeBallScript>(EvilEye2, player, movement, EvilEye2StateMachine, music);

    Entity* EvilEye3 = ObjectFactory::CreateEntity<Entity>();
    EvilEye3->GetTransform()->SetPosition(1204.0f, 702.0f);
    ObjectFactory::CreateComponent<Animator>(EvilEye3, Resources::instance().EVIL_EYE_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(EvilEye3, -15.0f, -15.0f, 15.0f, 15.0f);
    EvilEye3->GetComponent<AABBCollider>()->SetTrigger(true);
    EvilEye3->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* EvilEye3StateMachine = ObjectFactory::AttachScript<EntityStateScript>(EvilEye3, player, new IdleEyeBall);
    InteractEyeBallScript* EvilEye3Interact = ObjectFactory::AttachScript<InteractEyeBallScript>(EvilEye3, player, movement, EvilEye3StateMachine, music);

    
    quest = Engine::GetGameManager()->GetOrLoadGlobalScript<QuestScript>(player);
    //TODO Faire un get resource pour pouvoir savoir si arbre coupé
    quest->SetObjective(1, interaction->IsInteractingPointer());
    quest->SetObjective(3, Engine::GetScriptManager()->GetScript<EntityStateScript>(EvilEye1)->IsDead());

    EntityFactory::CreateBuilding(1170, 345, Resources::instance().RESOURCE_BUILDING_BLUE);

    bgm->AddMusic(1, "../../res/Music/BGM/plain_bgm.mp3");
    bgm->SetVolume(1);
    bgm->PlayBGMMusic(1);

}

void Beach::OnExit()
{
    Scene::OnExit();
    //bgm->StopBGMMusic();
    quest->RemoveObjective(1);
    quest->RemoveObjective(3);
}
