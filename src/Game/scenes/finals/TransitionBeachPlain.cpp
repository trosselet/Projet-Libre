#include "pch.h"
#include "TransitionBeachPlain.h"

#include "Beach.h"
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



void TransitionBeachPlain::OnEnter()
{
    Entity* cameraContainer = ObjectFactory::CreateEntity<Entity>();
    Camera* camera = ObjectFactory::CreateComponent<Camera>(cameraContainer);
    camera->ZoomFactor = 0.30f;

    Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Tilemap>(gridContainer, "../../res/Tiles/saved/plain_to_beach.txt");

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
    door->GetTransform()->SetPosition(480, 300);
    ObjectFactory::CreateComponent<SpriteRenderer>(door, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider = ObjectFactory::CreateComponent<AABBCollider>(door, 0, 0, 100, 200);
    doorCollider->SetStatic(true);
    doorCollider->SetTrigger(true);
    ObjectFactory::AttachScript<ZoneChanger<Village>>(door, zoneManager, 2650, 1290);

    Entity* door2 = ObjectFactory::CreateEntity<Entity>();
    door2->GetTransform()->SetPosition(1410, 300);
    ObjectFactory::CreateComponent<SpriteRenderer>(door2, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider2 = ObjectFactory::CreateComponent<AABBCollider>(door2, 0, 0, 100, 200);
    doorCollider2->SetStatic(true);
    doorCollider2->SetTrigger(true);
    ObjectFactory::AttachScript<ZoneChanger<Beach>>(door2, zoneManager, 100, 630);

    PlayerMovement* movement = ObjectFactory::AttachScript<PlayerMovement>(player, camera);
    movement->SetMapOffset({820.0f, 1150.0f}, {400.0f, 1040.0f});
    QuestScript* quest = Engine::GetGameManager()->GetOrLoadGlobalScript<QuestScript>(player);

	BGMMusicScript* bgm = ObjectFactory::AttachScript<BGMMusicScript>(player);

    bgm->AddMusic(1, "../../res/Music/BGM/plain_bgm.mp3");
    bgm->SetVolume(1);
    bgm->PlayBGMMusic(1);
    
}
