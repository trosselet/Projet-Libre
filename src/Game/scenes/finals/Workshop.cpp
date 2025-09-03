#include "pch.h"
#include "Workshop.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Tilemap.h"
#include "ECS/Entity.h"
#include "ObjectFactory.h"
#include "Resources.h"
#include "Beach.h"
#include "ECS/Components/Animator.h"
#include "scripts/PlayerMovement.h"
#include "scripts/BGMMusicScript.h"
#include "scripts/EntityFactory.h"
#include "scripts/EntityStateScript.h"
#include "scripts/interact/ZoneChanger.h"
#include "scripts/Inventory.h"
#include "scripts/MusicScript.h"
#include "scripts/PlayerMovement.h"
#include "scripts/QuestScript.h"
#include "scripts/StatistiqueScript.h"
#include "Transform.h"
#include "Transform.h"
#include "Village.h"
#include "scripts/interact/InteractCraftingStation.h"
#include "scripts/interact/InteractFrostGuardianScript.h"

void Workshop::OnEnter()
{
    Entity* cameraContainer = ObjectFactory::CreateEntity<Entity>();
    Camera* camera = ObjectFactory::CreateComponent<Camera>(cameraContainer);
    camera->ZoomFactor = 0.60f;

    Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Tilemap>(gridContainer, "../../res/Tiles/saved/house1.txt");

    Entity* player = ObjectFactory::CreateEntity<Entity>(50);
    ZoneManager* zoneManager = Engine::GetGameManager()->GetOrLoadGlobalScript<ZoneManager>(player);
    player->GetTransform()->SetPosition(zoneManager->GetPosition());
    ObjectFactory::CreateComponent<AABBCollider>(player, -15.0f, -5.0f, 15.0f, 25.0f);
    Animator* pAnim = ObjectFactory::CreateComponent<Animator>(player, Resources::instance().PLAYER_IDLE, 0.1f);
    Inventory* inventory = Engine::GetGameManager()->GetOrLoadGlobalScript<Inventory>(player);
    
    StatistiqueScript* playerStat = ObjectFactory::AttachScript<StatistiqueScript>(player, 20, 10, 0, 300);
    ObjectFactory::AttachScript<EntityStateScript>(player, player, new IdlePlayer);
    player->SetTag(Entity::Tag::PLAYER);

    BGMMusicScript* bgm = ObjectFactory::AttachScript<BGMMusicScript>(player);

    bgm->AddMusic(1, "../../res/Music/BGM/plain_bgm.mp3");
    bgm->SetVolume(1);
    bgm->PlayBGMMusic(1);

    MusicScript* music = ObjectFactory::AttachScript<MusicScript>(player, bgm);
    music->AddBeatmap(0, "../../res/Beatmaps/furnace_beatmap.txt", "../../res/Music/furnace.mp3", 191.95f, -60.f); // fingercontrol
    music->AddBeatmap(3, "../../res/Beatmaps/3.txt", "../../res/Music/3.mp3", 191.95f, -60.f); // fingercontrol

    Entity* door = ObjectFactory::CreateEntity<Entity>();
    door->GetTransform()->SetPosition(923 ,1045);
    ObjectFactory::CreateComponent<SpriteRenderer>(door, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider = ObjectFactory::CreateComponent<AABBCollider>(door, 0, 0, 200, 100);
    doorCollider->SetStatic(true);
    doorCollider->SetTrigger(true);
    ObjectFactory::AttachScript<ZoneChanger<Village>>(door, zoneManager, 895,  879);
    
    PlayerMovement* movement = ObjectFactory::AttachScript<PlayerMovement>(player, camera);
    movement->SetMapOffset({1190.0f, 1670.f}, {550.0f, 800.0f});

    Entity* FrostGuardian3 = ObjectFactory::CreateEntity<Entity>();
    FrostGuardian3->GetTransform()->SetPosition(1019.0f, 395.0f);
    ObjectFactory::CreateComponent<Animator>(FrostGuardian3, Resources::instance().FROST_GUARDIAN_IDLE, 0.1f);
    ObjectFactory::CreateComponent<AABBCollider>(FrostGuardian3, -45.0f, -45.0f, 45.0f, 45.0f);
    FrostGuardian3->GetComponent<AABBCollider>()->SetTrigger(true);
    FrostGuardian3->SetTag(Entity::Tag::ENNEMY);
    EntityStateScript* FrostGuardian3StateMachine = ObjectFactory::AttachScript<EntityStateScript>(FrostGuardian3, player, new IdleFrostGuardian);
    InteractFrostGuardianScript* FrostGuardian3Interact = ObjectFactory::AttachScript<InteractFrostGuardianScript>(FrostGuardian3, player, movement, FrostGuardian3StateMachine, music);


    Entity* armorContainer = ObjectFactory::CreateEntity<Entity>();
    armorContainer->GetTransform()->SetPosition(1754, 605);
    armorContainer->GetTransform()->SetScale({2.0f, 2.0f});
    ObjectFactory::CreateComponent<Animator>(armorContainer, Resources::instance().ANVIL, 0.1f);
    AABBCollider* collider3 = ObjectFactory::CreateComponent<AABBCollider>(armorContainer, -50, -10, 50, 70);
    collider3->SetStatic(true);
    collider3->SetTrigger(true);

    Entity* armorCollider = ObjectFactory::CreateEntity<Entity>(armorContainer);
    AABBCollider* armorC = ObjectFactory::CreateComponent<AABBCollider>(armorCollider, -50, -10, 50, 50);
    armorC->SetStatic(true);
    
    Craft* armorBench = ObjectFactory::AttachScript<Craft>(armorContainer, inventory, bgm, music, "Enclume");
    ObjectFactory::AttachScript<InteractCraftingStation>(armorContainer, player, movement, armorBench, music);
    armorBench->AddCraft("Epée en bois", 0,
                           {
                               {Material::PLANK_BASIC, 15},
                               {Material::PLANK_DARK_OAK, 10},
                           },
                           {
                               {0.1f, Result{inventory->Items[Material::WOODEN_SWORD], 1, 1}},
                               {0.5f, Result{inventory->Items[Material::ENCHANTED_SWORD], 1, 1}},
                               {0.8f, Result{inventory->Items[Material::SHARP_WOOD_SWORD], 1, 1}},
                               {0.99f, Result{inventory->Items[Material::HEAVY_WOOD_SWORD], 1, 1}}
                           });
    armorBench->AddCraft("Epée en fer", 0,
                       {
                           {Material::PLANK_BASIC, 10},
                           {Material::IRON_INGOT, 5},
                       },
                       {
                           {0.1f, Result{inventory->Items[Material::STONE_SWORD], 1, 1}},
                           {0.5f, Result{inventory->Items[Material::REFINED_IRON_KATANA], 1, 1}},
                           {0.8f, Result{inventory->Items[Material::IRON_SWORD], 1, 1}},
                           {0.99f, Result{inventory->Items[Material::LIVING_WOOD_STEEL_SWORD], 1, 1}}
                       });

    armorBench->AddCraft("Casque en fer", 0,
               {
                   {Material::PLANK_BASIC, 10},
                   {Material::IRON_INGOT, 7},
               },
               {
                   {0.1f, Result{inventory->Items[Material::TOP_GRAIN_LEATHER_HELMET], 1, 1}},
                   {0.5f, Result{inventory->Items[Material::CHAINMAIL_HELMET], 1, 1}},
                   {0.8f, Result{inventory->Items[Material::IRON_HELMET], 1, 1}},
                   {0.99f, Result{inventory->Items[Material::GOLD_HELMET], 1, 1}}
               });

    armorBench->AddCraft("Plastron en fer", 0,
           {
               {Material::PLANK_BASIC, 16},
               {Material::IRON_INGOT, 10},
           },
           {
               {0.1f, Result{inventory->Items[Material::TOP_GRAIN_LEATHER_BREASTPLATE], 1, 1}},
               {0.5f, Result{inventory->Items[Material::CHAINMAIL_BREASTPLATE], 1, 1}},
               {0.8f, Result{inventory->Items[Material::IRON_BREASTPLATE], 1, 1}},
               {0.99f, Result{inventory->Items[Material::GOLD_BREASTPLATE], 1, 1}}
           });

    armorBench->AddCraft("Pantalon en fer", 0,
       {
           {Material::PLANK_BASIC, 14},
           {Material::IRON_INGOT, 8},
       },
       {
           {0.1f, Result{inventory->Items[Material::TOP_GRAIN_LEATHER_PANTS], 1, 1}},
           {0.5f, Result{inventory->Items[Material::CHAINMAIL_PANTS], 1, 1}},
           {0.8f, Result{inventory->Items[Material::IRON_PANTS], 1, 1}},
           {0.99f, Result{inventory->Items[Material::GOLD_PANTS], 1, 1}}
       });

    armorBench->AddCraft("Bottes en fer", 0,
       {
           {Material::PLANK_BASIC, 10},
           {Material::IRON_INGOT, 5},
       },
       {
           {0.1f, Result{inventory->Items[Material::TOP_GRAIN_LEATHER_BOOTS], 1, 1}},
           {0.5f, Result{inventory->Items[Material::CHAINMAIL_BOOTS], 1, 1}},
           {0.8f, Result{inventory->Items[Material::IRON_BOOTS], 1, 1}},
           {0.99f, Result{inventory->Items[Material::GOLD_BOOTS], 1, 1}}
       });

    QuestScript* quest = Engine::GetGameManager()->GetOrLoadGlobalScript<QuestScript>(player);
    
}
