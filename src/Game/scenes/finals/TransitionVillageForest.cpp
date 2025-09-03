#include "pch.h"
#include "TransitionVillageForest.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Animator.h"
#include "ECS/Components/Tilemap.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "scripts/Inventory.h"
#include "Forest.h"
#include "Village.h"
#include "ECS/Components/Animator.h"
#include "scripts/PlayerMovement.h"
#include "scripts/BGMMusicScript.h"
#include "scripts/EntityFactory.h"
#include "scripts/MusicScript.h"
#include "scripts/interact/ZoneChanger.h"
#include "scripts/EntityStateScript.h"
#include "scripts/QuestScript.h"
#include "scripts/StatistiqueScript.h"


void TransitionVillageForest::OnEnter()
{
    Entity* cameraContainer = ObjectFactory::CreateEntity<Entity>();
    Camera* camera = ObjectFactory::CreateComponent<Camera>(cameraContainer);
    camera->ZoomFactor = 0.250f;

    Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Tilemap>(gridContainer, "../../res/Tiles/saved/village_to_forest.txt");

    Entity* player = ObjectFactory::CreateEntity<Entity>(50);

    ZoneManager* zoneManager = Engine::GetGameManager()->GetOrLoadGlobalScript<ZoneManager>(player);
    player->GetTransform()->SetPosition(zoneManager->GetPosition());

    Engine::GetGameManager()->GetOrLoadGlobalScript<Inventory>(player);
    ObjectFactory::CreateComponent<AABBCollider>(player, -15.0f, -5.0f, 15.0f, 25.0f);
    Animator* pAnim = ObjectFactory::CreateComponent<Animator>(player, Resources::instance().PLAYER_IDLE, 0.1f);
    player->SetTag(Entity::Tag::PLAYER);

    StatistiqueScript* playerStat = ObjectFactory::AttachScript<StatistiqueScript>(player, 20, 10, 0, 300);
    ObjectFactory::AttachScript<EntityStateScript>(player, player, new IdlePlayer);

    Entity* door = ObjectFactory::CreateEntity<Entity>();
    door->GetTransform()->SetPosition(450, 155);
    ObjectFactory::CreateComponent<SpriteRenderer>(door, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider = ObjectFactory::CreateComponent<AABBCollider>(door, 0, 0, 150, 25);
    doorCollider->SetStatic(true);
    doorCollider->SetTrigger(true);
    ObjectFactory::AttachScript<ZoneChanger<Forest>>(door, zoneManager, 400, 400); // TODO    
    
    Entity* door2 = ObjectFactory::CreateEntity<Entity>();
    door2->GetTransform()->SetPosition(450, 655);
    ObjectFactory::CreateComponent<SpriteRenderer>(door2, Resources::instance().DEFAULT_SPRITE);
    AABBCollider* doorCollider2 = ObjectFactory::CreateComponent<AABBCollider>(door2, 0, 0, 150, 25);
    doorCollider2->SetStatic(true);
    doorCollider2->SetTrigger(true);
    ObjectFactory::AttachScript<ZoneChanger<Village>>(door2, zoneManager, 2015, 85); // TODO
    
    player->SetTag(Entity::Tag::PLAYER);
	QuestScript* quest = Engine::GetGameManager()->GetOrLoadGlobalScript<QuestScript>(player);

    PlayerMovement* movement = ObjectFactory::AttachScript<PlayerMovement>(player, camera);
    movement->SetMapOffset({500.0f, 580.0f}, {300.0f, 550.0f });

    BGMMusicScript* bgm = ObjectFactory::AttachScript<BGMMusicScript>(player);

    bgm->AddMusic(1, "../../res/Music/BGM/plain_bgm.mp3");
    bgm->SetVolume(1);
    bgm->PlayBGMMusic(1);
}
