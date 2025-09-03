#include "pch.h"
#include "Village.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Tilemap.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/Animator.h"
#include "ECS/Components/ui/Button.h"
#include "Managers/GameManager.h"
#include "scripts/EntityFactory.h"
#include "scripts/interact/InteractCraftingStation.h"
#include "scripts/interact/ResourceInteraction.h"
#include "scripts/interact/InteractEyeBallScript.h"
#include "scripts/interact/InteractFrostGuardianScript.h"
#include "scripts/interact/InteractGrolux.h"
#include "scripts/resources/Craft.h"
#include "scripts/tilemap/TilemapEditor.h"
#include "scripts/StatistiqueScript.h"
#include "scripts/EntityStateScript.h"
#include "scenes/finals/Forest.h"
#include "Shop.h"
#include "TransitionVillageForest.h"
#include "TransitionBeachPlain.h"
#include "Workshop.h"
#include "scripts/interact/ZoneChanger.h"
#include "scripts/QuestScript.h"
#include "scripts/menus/PauseMenu.h"


void Village::OnEnter()
{
    
    Entity* cameraContainer = ObjectFactory::CreateEntity<Entity>();
    Camera* camera = ObjectFactory::CreateComponent<Camera>(cameraContainer);
    camera->ZoomFactor = 0.65f;
    
    Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Tilemap>(gridContainer, "../../res/Tiles/saved/village.txt");

    Entity* player = ObjectFactory::CreateEntity<Entity>(50);
    ObjectFactory::CreateComponent<AABBCollider>(player, -15.0f, -5.0f, 15.0f, 25.0f);
    ObjectFactory::AttachScript<PauseMenu>(player);

    ZoneManager* zoneManager = Engine::GetGameManager()->GetOrLoadGlobalScript<ZoneManager>(player);
    player->GetTransform()->SetPosition(zoneManager->GetPosition());

    Animator* pAnim = ObjectFactory::CreateComponent<Animator>(player, Resources::instance().PLAYER_IDLE, 0.1f);

    StatistiqueScript* playerStat = ObjectFactory::AttachScript<StatistiqueScript>(player, 20, 10, 0, 300);
    ObjectFactory::AttachScript<EntityStateScript>(player, player, new IdlePlayer);
    player->SetTag(Entity::Tag::PLAYER);

    bgm = ObjectFactory::AttachScript<BGMMusicScript>(player);

    bgm->AddMusic(1, "../../res/Music/BGM/plain_bgm.mp3");
    bgm->SetVolume(10);
    bgm->PlayBGMMusic(1);

    MusicScript* music = ObjectFactory::AttachScript<MusicScript>(player, bgm);

    music->AddBeatmap(1, "../../res/Beatmaps/5.txt", "../../res/Music/5.mp3", 191.95f, -60.f); // fingercontrol
    music->AddBeatmap(2, "../../res/Beatmaps/4.txt", "../../res/Music/4.ogg", 260.f, 40.f); // high bpm
    music->AddBeatmap(3, "../../res/Beatmaps/3.txt", "../../res/Music/3.mp3", 129.25f, -100.f);
    music->AddBeatmap(4, "../../res/Beatmaps/8.txt", "../../res/Music/8.mp3", 222.f, -100.f);
    music->AddBeatmap(5, "../../res/Beatmaps/wood_beatmap.txt", "../../res/Music/wood.mp3", 260.f, 40.f); // high bpm
    music->AddBeatmap(6, "../../res/Beatmaps/furnace_beatmap.txt", "../../res/Music/furnace.mp3", 191.95f, -60.f); // fingercontrol

    PlayerMovement* movement = ObjectFactory::AttachScript<PlayerMovement>(player, camera);
    movement->SetMapOffset({ 630.0f, 2195.0f }, { 360.0f, 1210.0f });  // DO NOT TOUCH
    
    Entity* canvas = ObjectFactory::CreateEntity<Entity>();
    Entity* invContainer = ObjectFactory::CreateEntity<Entity>(canvas);
    Inventory* inventory = Engine::GetGameManager()->GetOrLoadGlobalScript<Inventory>(player);
    
    Entity* woodWorkbenchContainer = ObjectFactory::CreateEntity<Entity>(canvas);
    woodWorkbenchContainer->GetTransform()->SetPosition(465, 835);
    woodWorkbenchContainer->GetTransform()->SetScale({1.5f, 1.5f});
    ObjectFactory::CreateComponent<SpriteRenderer>(woodWorkbenchContainer, Resources::instance().WORKSTATION);
    AABBCollider* collider = ObjectFactory::CreateComponent<AABBCollider>(woodWorkbenchContainer, -50, -25, 25, 50);
    collider->SetStatic(true);
    collider->SetTrigger(true);

    Entity* woodWorkbenchCollider = ObjectFactory::CreateEntity<Entity>(woodWorkbenchContainer);
    AABBCollider* woodWorkbench = ObjectFactory::CreateComponent<AABBCollider>(woodWorkbenchCollider, -50, -25, 25, 25);
    woodWorkbench->SetStatic(true);
    
    Craft* woodworkBench = ObjectFactory::AttachScript<Craft>(woodWorkbenchContainer, inventory, bgm, music, "Etabli");
    InteractCraftingStation* craftStation = ObjectFactory::AttachScript<InteractCraftingStation>(woodWorkbenchContainer, player, movement, woodworkBench, music);
    woodworkBench->AddCraft("Planches", 3,
                           {
                               {Material::WOOD_BASIC, 10},
                           },
                           {
                               {0.1f, Result{inventory->Items[Material::PLANK_BASIC], 2, 4}},
                               {0.5f, Result{inventory->Items[Material::PLANK_BASIC], 4, 10}},
                               {0.8f, Result{inventory->Items[Material::PLANK_BASIC], 9, 10}},
                               {0.99f, Result{inventory->Items[Material::PLANK_BASIC], 40, 50}}
                           });
    
    woodworkBench->AddCraft("Planches noires", 3,
                           {
                               {Material::WOOD_BASIC, 7},
                               {Material::WOOD_DARK_OAK, 10},
                           },
                           {
                               {0.1f, Result{inventory->Items[Material::PLANK_DARK_OAK], 2, 4}},
                               {0.5f, Result{inventory->Items[Material::PLANK_DARK_OAK], 4, 10}},
                               {0.8f, Result{inventory->Items[Material::PLANK_DARK_OAK], 9, 10}},
                               {0.99f, Result{inventory->Items[Material::PLANK_DARK_OAK], 40, 50}}
                           });

    woodworkBench->AddCraft("Planches noires", 3,
                       {
                           {Material::WOOD_BASIC, 4},
                           {Material::WOOD_DARK_OAK, 5},
                           {Material::WOOD_PALM, 10},
                       },
                       {
                           {0.1f, Result{inventory->Items[Material::PLANK_PALM_WOOD], 2, 4}},
                           {0.5f, Result{inventory->Items[Material::PLANK_PALM_WOOD], 4, 10}},
                           {0.8f, Result{inventory->Items[Material::PLANK_PALM_WOOD], 9, 10}},
                           {0.99f, Result{inventory->Items[Material::PLANK_PALM_WOOD], 40, 50}}
                       });

    Entity* furnaceContainer = ObjectFactory::CreateEntity<Entity>(canvas);
    furnaceContainer->GetTransform()->SetPosition(1115, 985);
    furnaceContainer->GetTransform()->SetScale({1.0f, 1.0f});
    ObjectFactory::CreateComponent<Animator>(furnaceContainer, Resources::instance().FURNACE, 0.1f);
    AABBCollider* collider2 = ObjectFactory::CreateComponent<AABBCollider>(furnaceContainer, 0, 0, 50, 50);
    collider2->SetStatic(true);
    collider2->SetTrigger(true);

    Entity* furnaceCollider = ObjectFactory::CreateEntity<Entity>(furnaceContainer);
    AABBCollider* furnacebench = ObjectFactory::CreateComponent<AABBCollider>(furnaceCollider, -25, -25, 25, 25);
    furnacebench->SetStatic(true);
    
    Craft* furnaceBench = ObjectFactory::AttachScript<Craft>(furnaceContainer, inventory, bgm, music, "Four");
    ObjectFactory::AttachScript<InteractCraftingStation>(furnaceContainer, player, movement, furnaceBench, music);
    furnaceBench->AddCraft("Charbon", 6,
                           {
                               {Material::WOOD_BASIC, 10},
                           },
                           {
                               {0.1f, Result{inventory->Items[Material::COAL], 1, 2}},
                               {0.5f, Result{inventory->Items[Material::COAL], 2, 3}},
                               {0.8f, Result{inventory->Items[Material::COAL], 3, 4}},
                               {0.99f, Result{inventory->Items[Material::COAL], 4, 6}}
                           });
    
    furnaceBench->AddCraft("Pierre taillee", 6,
                           {
                               {Material::STONE, 10},
                           },
                           {
                                   {0.1f, Result{inventory->Items[Material::REFINED_STONE], 1, 2}},
                                   {0.5f, Result{inventory->Items[Material::REFINED_STONE], 2, 3}},
                                   {0.8f, Result{inventory->Items[Material::REFINED_STONE], 3, 4}},
                                   {0.99f, Result{inventory->Items[Material::REFINED_STONE], 4, 6}}
                           });

    furnaceBench->AddCraft("Lingot de cuivre", 6,
                           {
                               {Material::COAL, 10},
                                {Material::COPPER, 15},
                           },
                           {
                               {0.1f, Result{inventory->Items[Material::COPPER_INGOT], 1, 2}},
                               {0.5f, Result{inventory->Items[Material::COPPER_INGOT], 2, 3}},
                               {0.8f, Result{inventory->Items[Material::COPPER_INGOT], 3, 4}},
                               {0.99f, Result{inventory->Items[Material::COPPER_INGOT], 4, 5}}
                           });

    furnaceBench->AddCraft("Lingot de fer", 6,
                       {
                           {Material::COAL, 10},
                           {Material::IRON, 15},
                       },
                       {
                           {0.1f, Result{inventory->Items[Material::IRON_INGOT], 1, 2}},
                           {0.5f, Result{inventory->Items[Material::IRON_INGOT], 2, 3}},
                           {0.8f, Result{inventory->Items[Material::IRON_INGOT], 3, 4}},
                           {0.99f, Result{inventory->Items[Material::IRON_INGOT], 5, 6}}
                       });

    furnaceBench->AddCraft("Lingot de steel", 6,
                   {
                       {Material::COAL, 10},
                        {Material::IRON_INGOT, 20},
                   },
                   {
                       {0.1f, Result{inventory->Items[Material::STEEL], 1, 2}},
                       {0.5f, Result{inventory->Items[Material::STEEL], 2, 3}},
                       {0.8f, Result{inventory->Items[Material::STEEL], 3, 4}},
                       {0.99f, Result{inventory->Items[Material::STEEL], 4, 5}}
                   });
    
    
    LootTable treeTable = LootTable{ WOOD_BASIC,
        {
                {0.5f, 1},
                {0.8f, 3},
                {0.99f, 5}
        }
    };

    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1457, 732, 100, 100, 5);
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1697, 752, 100, 100, 5);
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1517, 840, 100, 100, 5);
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1617, 883, 100, 100, 5);
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1767, 983, 100, 100, 5);
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1487, 1013, 100, 100,5);
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1507, 1313, 100, 100, 5);
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1493, 209, 100, 100, 5);
    EntityFactory::CreateResource(music, player, movement, inventory, treeTable, 1653, 239, 100, 100, 5);

    
    EntityFactory::CreateBuilding(900, 400, Resources::instance().RESOURCE_BUILDING_BLUE2);
    EntityFactory::CreateBuilding(1130, 430, Resources::instance().RESOURCE_BUILDING_GREEN);

    EntityFactory::CreateBuilding(900, 730, Resources::instance().RESOURCE_BUILDING_GREEN2);
    EntityFactory::CreateBuilding(1130, 760, Resources::instance().RESOURCE_BUILDING_BLUE);

    EntityFactory::CreateBuilding(300, 430, Resources::instance().RESOURCE_BUILDING_BLUE);
    EntityFactory::CreateBuilding(530, 400, Resources::instance().RESOURCE_BUILDING_GREEN2);

    EntityFactory::CreateBuilding(205, 700, Resources::instance().RESOURCE_BUILDING_SHOP);
    EntityFactory::CreateBuilding(200, 940, Resources::instance().RESOURCE_BUILDING_MEDIC);

    Entity* door = ObjectFactory::CreateEntity<Entity>();
    door->GetTransform()->SetPosition(1950, 0);
    ObjectFactory::CreateComponent<SpriteRenderer>(door, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider = ObjectFactory::CreateComponent<AABBCollider>(door, 0, 0, 200, 40);
    doorCollider->SetTrigger(true);
    doorCollider->SetStatic(true);
    ObjectFactory::AttachScript<ZoneChanger<TransitionVillageForest>>(door, zoneManager, 540, 610);

    Entity* door2 = ObjectFactory::CreateEntity<Entity>();
    door2->GetTransform()->SetPosition(2790, 1170);
    ObjectFactory::CreateComponent<SpriteRenderer>(door2, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider2 = ObjectFactory::CreateComponent<AABBCollider>(door2, 0, 0, 100, 300);
    doorCollider2->SetTrigger(true);
    ObjectFactory::AttachScript<ZoneChanger<TransitionBeachPlain>>(door2, zoneManager, 650, 385);

    Entity* door3 = ObjectFactory::CreateEntity<Entity>();
    door3->GetTransform()->SetPosition(195,  765);
    ObjectFactory::CreateComponent<SpriteRenderer>(door3, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider3 = ObjectFactory::CreateComponent<AABBCollider>(door3, 0, 0, 10, 10);
    doorCollider3->SetTrigger(true);
    ObjectFactory::AttachScript<ZoneChanger<Shop>>(door3, zoneManager, 200, 385);
    
    Entity* door4 = ObjectFactory::CreateEntity<Entity>();
    door4->GetTransform()->SetPosition(895,  839);
    ObjectFactory::CreateComponent<SpriteRenderer>(door4, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider4 = ObjectFactory::CreateComponent<AABBCollider>(door4, 0, 0, 10, 10);
    doorCollider4->SetTrigger(true);
    ObjectFactory::AttachScript<ZoneChanger<Workshop>>(door4, zoneManager, 1015, 1015);

    Entity* EvilEye1 = ObjectFactory::CreateEntity<Entity>();
    EvilEye1->GetTransform()->SetPosition(2704.0f, 1302.0f);
    ObjectFactory::CreateComponent<Animator>(EvilEye1, Resources::instance().EVIL_EYE_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(EvilEye1, -15.0f, -15.0f, 15.0f, 15.0f);
    EvilEye1->GetComponent<AABBCollider>()->SetTrigger(true);
    EvilEye1->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* EvilEye1StateMachine = ObjectFactory::AttachScript<EntityStateScript>(EvilEye1, player, new IdleEyeBall);
    InteractEyeBallScript* EvilEye1Interact = ObjectFactory::AttachScript<InteractEyeBallScript>(EvilEye1, player, movement, EvilEye1StateMachine, music);

    Entity* EvilEye2 = ObjectFactory::CreateEntity<Entity>();
    EvilEye2->GetTransform()->SetPosition(2704.0f, 1270.0f);
    ObjectFactory::CreateComponent<Animator>(EvilEye2, Resources::instance().EVIL_EYE_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(EvilEye2, -15.0f, -15.0f, 15.0f, 15.0f);
    EvilEye2->GetComponent<AABBCollider>()->SetTrigger(true);
    EvilEye2->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* EvilEye2StateMachine = ObjectFactory::AttachScript<EntityStateScript>(EvilEye2, player, new IdleEyeBall);
    InteractEyeBallScript* EvilEye2Interact = ObjectFactory::AttachScript<InteractEyeBallScript>(EvilEye2, player, movement, EvilEye2StateMachine, music);

    Entity* EvilEye3 = ObjectFactory::CreateEntity<Entity>();
    EvilEye3->GetTransform()->SetPosition(2704.0f, 1337.0f);
    ObjectFactory::CreateComponent<Animator>(EvilEye3, Resources::instance().EVIL_EYE_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(EvilEye3, -15.0f, -15.0f, 15.0f, 15.0f);
    EvilEye3->GetComponent<AABBCollider>()->SetTrigger(true);
    EvilEye3->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* EvilEye3StateMachine = ObjectFactory::AttachScript<EntityStateScript>(EvilEye3, player, new IdleEyeBall);
    InteractEyeBallScript* EvilEye3Interact = ObjectFactory::AttachScript<InteractEyeBallScript>(EvilEye3, player, movement, EvilEye3StateMachine, music);
    
    Entity* FrostGuardian1 = ObjectFactory::CreateEntity<Entity>();
    FrostGuardian1->GetTransform()->SetPosition(2520.f, 952.0f);
    ObjectFactory::CreateComponent<Animator>(FrostGuardian1, Resources::instance().FROST_GUARDIAN_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(FrostGuardian1, -45.0f, -45.0f, 45.0f, 45.0f);
    FrostGuardian1->GetComponent<AABBCollider>()->SetTrigger(true);
    FrostGuardian1->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* FrostGuardian1StateMachine = ObjectFactory::AttachScript<EntityStateScript>(FrostGuardian1, player, new IdleFrostGuardian);
    InteractFrostGuardianScript* FrostGuardian1Interact = ObjectFactory::AttachScript<InteractFrostGuardianScript>(FrostGuardian1, player, movement, FrostGuardian1StateMachine, music);

    Entity* FrostGuardian2 = ObjectFactory::CreateEntity<Entity>();
    FrostGuardian2->GetTransform()->SetPosition(2504.0f, 802.0f);
    ObjectFactory::CreateComponent<Animator>(FrostGuardian2, Resources::instance().FROST_GUARDIAN_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(FrostGuardian2, -45.0f, -45.0f, 45.0f, 45.0f);
    FrostGuardian2->GetComponent<AABBCollider>()->SetTrigger(true);
    FrostGuardian2->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* FrostGuardian2StateMachine = ObjectFactory::AttachScript<EntityStateScript>(FrostGuardian2, player, new IdleFrostGuardian);
    InteractFrostGuardianScript* FrostGuardian2Interact = ObjectFactory::AttachScript<InteractFrostGuardianScript>(FrostGuardian2, player, movement, FrostGuardian2StateMachine, music);
    
    Entity* FrostGuardian3 = ObjectFactory::CreateEntity<Entity>();
    FrostGuardian3->GetTransform()->SetPosition(2704.0f, 902.0f);
    ObjectFactory::CreateComponent<Animator>(FrostGuardian3, Resources::instance().FROST_GUARDIAN_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(FrostGuardian3, -45.0f, -45.0f, 45.0f, 45.0f);
    FrostGuardian3->GetComponent<AABBCollider>()->SetTrigger(true);
    FrostGuardian3->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* FrostGuardian3StateMachine = ObjectFactory::AttachScript<EntityStateScript>(FrostGuardian3, player, new IdleFrostGuardian);
    InteractFrostGuardianScript* FrostGuardian3Interact = ObjectFactory::AttachScript<InteractFrostGuardianScript>(FrostGuardian3, player, movement, FrostGuardian3StateMachine, music);

    quest = Engine::GetGameManager()->GetOrLoadGlobalScript<QuestScript>(player);
    quest->SetState(false);
    if (!quest->HasQuest())
    {
        quest->AddQuest(0, "Aller à la plage");
        quest->AddQuest(1, "Couper un arbre");
        quest->AddQuest(2, "Aller dans une table de craft");
        quest->AddQuest(3, "Tuer un/ou plusieurs evil eye");
        quest->AddQuest(4, "Tuer un/ou plusieurs guardian");
        quest->AddQuest(5, "Tuer Grolux");
        quest->AddQuest(6, "           ");
    }

    quest->SetObjective(0, &Engine::GetScriptManager()->GetScript<ZoneChanger<TransitionBeachPlain>>(door2)->enter);
    quest->SetObjective(2, craftStation->IsInteractingPointer());
    quest->SetObjective(4, Engine::GetScriptManager()->GetScript<EntityStateScript>(FrostGuardian1)->IsDead());
}

void Village::OnExit()
{
    Scene::OnExit();
    bgm->StopBGMMusic();
    quest->RemoveObjective(0);
    quest->RemoveObjective(2);
    quest->RemoveObjective(4);
}
