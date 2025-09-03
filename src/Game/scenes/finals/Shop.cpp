#include "pch.h"
#include "Shop.h"
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

void Shop::OnEnter()
{
    Entity* cameraContainer = ObjectFactory::CreateEntity<Entity>();
    Camera* camera = ObjectFactory::CreateComponent<Camera>(cameraContainer);
    camera->ZoomFactor = 0.25f;

    Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Tilemap>(gridContainer, "../../res/Tiles/saved/house.txt");

    Entity* player = ObjectFactory::CreateEntity<Entity>(50);
    ZoneManager* zoneManager = Engine::GetGameManager()->GetOrLoadGlobalScript<ZoneManager>(player);
    player->GetTransform()->SetPosition(zoneManager->GetPosition());
    ObjectFactory::CreateComponent<AABBCollider>(player, -15.0f, -5.0f, 15.0f, 25.0f);
    Animator* pAnim = ObjectFactory::CreateComponent<Animator>(player, Resources::instance().PLAYER_IDLE, 0.1f);
    Engine::GetGameManager()->GetOrLoadGlobalScript<Inventory>(player);
    
    StatistiqueScript* playerStat = ObjectFactory::AttachScript<StatistiqueScript>(player, 20, 10, 0, 300);
    ObjectFactory::AttachScript<EntityStateScript>(player, player, new IdlePlayer);
    player->SetTag(Entity::Tag::PLAYER);


    Entity* door = ObjectFactory::CreateEntity<Entity>();
    door->GetTransform()->SetPosition(390 ,510);
    ObjectFactory::CreateComponent<SpriteRenderer>(door, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider = ObjectFactory::CreateComponent<AABBCollider>(door, 0, 0, 10, 10);
    doorCollider->SetStatic(true);
    doorCollider->SetTrigger(true);
    ObjectFactory::AttachScript<ZoneChanger<Village>>(door, zoneManager, 195, 785);


    PlayerMovement* movement = ObjectFactory::AttachScript<PlayerMovement>(player, camera);
    movement->SetMapOffset({370.0f, 410.f}, {180.0f, 430.0f});

	BGMMusicScript* bgm = ObjectFactory::AttachScript<BGMMusicScript>(player);

    bgm->AddMusic(1, "../../res/Music/BGM/plain_bgm.mp3");
    bgm->SetVolume(1);
    bgm->PlayBGMMusic(1);
    
    QuestScript* quest = Engine::GetGameManager()->GetOrLoadGlobalScript<QuestScript>(player);
}
