#include "pch.h"
#include "ThomasScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/ui/Image.h"
#include "ECS/Components/Animator.h"

#include "scripts/PlayerMovement.h"
#include "scripts/EntityStateScript.h"
#include "scripts/interact/InteractEyeBallScript.h"
#include "scripts/interact/InteractFrostGuardianScript.h"
#include "scripts/QuestScript.h"
#include "scripts/ParticlesScript.h"
#include "scripts/StatistiqueScript.h"

#include "scripts/state-machine/State.h"

void ThomasScene::OnEnter()
{
    //srand(static_cast<unsigned int>(time(nullptr)));

    ///*OTHERS*/

    //Entity* camera = ObjectFactory::CreateEntity<Entity>();
    //ObjectFactory::CreateComponent<Camera>(camera);

    //Entity* expBar = ObjectFactory::CreateEntity<Entity>();
    //ObjectFactory::CreateComponent<Image>(expBar, Resources::instance().DEFAULT_SPRITE);

    ///*PLAYER*/

    //Entity* player = ObjectFactory::CreateEntity<Entity>();
    //player->GetTransform()->SetPosition(960.0f, 540.0f);
    //ObjectFactory::CreateComponent<AABBCollider>(player, -5.0f, -15.0f, 5.0f, 15.0f);
    //ObjectFactory::CreateComponent<Animator>(player, "../../res/Textures/player/Idle.png", 0, 0, 80, 48, 80, 48, 0.1f);
    //player->SetTag(Entity::Tag::PLAYER);

    //MusicScript* music = ObjectFactory::AttachScript<MusicScript>(player);

    //StatistiqueScript* playerStat = ObjectFactory::AttachScript<StatistiqueScript>(player, 20, 10, 0, 300);
    //PlayerMovement* playerMovement = ObjectFactory::AttachScript<PlayerMovement>(player, camera->GetComponent<Camera>());
    //ObjectFactory::AttachScript<EntityStateScript>(player, player, new IdlePlayer);
    //ObjectFactory::AttachScript<ParticlesScript>(player, 200);

    ///*MONSTER*/

    ////EyeBall

    //Entity* monster = ObjectFactory::CreateEntity<Entity>();
    //monster->GetTransform()->SetPosition(100.0f, 100.0f);
    //ObjectFactory::CreateComponent<Animator>(monster, "../../res/Textures/Monsters/EvilEye/Idle/sprite_sheet.png", 0, 0, 60, 57, 1200, 57, 0.1f);
    //ObjectFactory::CreateComponent<AABBCollider>(monster, -15.0f, -15.0f, 15.0f, 15.0f);
    //monster->GetComponent<AABBCollider>()->SetTrigger(true);
    //monster->SetTag(Entity::Tag::ENNEMY);

    //EntityStateScript* monsterStateMachine = ObjectFactory::AttachScript<EntityStateScript>(monster, new IdleEyeBall);
    //InteractEyeBallScript* eyeBallInteract = ObjectFactory::AttachScript<InteractEyeBallScript>(monster, player, playerMovement, monsterStateMachine, music);

    ////FrostGuardian

    //Entity* frostGuardian = ObjectFactory::CreateEntity<Entity>();

    //StatistiqueScript* frostGuardianStat = ObjectFactory::AttachScript<StatistiqueScript>(frostGuardian, 100, 20, 20, 300);

    //frostGuardian->GetTransform()->SetPosition(960.0f, 540.0f);
    //ObjectFactory::CreateComponent<Animator>(frostGuardian, "../../res/Textures/Monsters/FrostGuardian/Idle/spritesheet.png", 0, 0, 60, 57, 1152, 128, 0.1f);
    //ObjectFactory::CreateComponent<AABBCollider>(frostGuardian, -45.0f, -45.0f, 45.0f, 45.0f);
    //frostGuardian->GetComponent<AABBCollider>()->SetTrigger(true);
    //frostGuardian->SetTag(Entity::Tag::ENNEMY);

    //EntityStateScript* frostGuardianStateMachine = ObjectFactory::AttachScript<EntityStateScript>(frostGuardian, new IdleFrostGuardian);
    //InteractFrostGuardianScript* frostGuardianInteract = ObjectFactory::AttachScript<InteractFrostGuardianScript>(frostGuardian, player, playerMovement, frostGuardianStateMachine, music);
    //


    ///*QUEST*/

}

void ThomasScene::OnUpdate()
{

}