#include "pch.h"
#include "EntityFactory.h"

#include "MusicScript.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "interact/ResourceInteraction.h"

ResourceInteraction* EntityFactory::CreateResource(MusicScript* music, Entity* player, PlayerMovement* playerMovement, Inventory* inventory, LootTable lootTable, float x, float y, float sizeX, float sizeY, int audioBeatmap)
{
    Entity* resource = ObjectFactory::CreateEntity<Entity>();
    resource->GetTransform()->SetPosition(x, y);
    resource->SetTag(Entity::Tag::OBSTACLE);
    ObjectFactory::CreateComponent<AABBCollider>(resource, 0, 0, sizeX, sizeY);
    AABBCollider* resCollider = ObjectFactory::CreateComponent<AABBCollider>(resource, 0, 0, sizeX, sizeY);
    resCollider->SetTrigger(true);
    
    return ObjectFactory::AttachScript<ResourceInteraction>(resource, player, playerMovement, music, inventory, lootTable, audioBeatmap);

}

void EntityFactory::CreateBuilding(int x, int y, Sprite* sprite)
{
    Entity* build = ObjectFactory::CreateEntity<Entity>();
    build->GetTransform()->SetPosition(x, y);
    build->GetTransform()->SetScale({ 2.0f, 2.0f });
    build->SetTag(Entity::Tag::OBSTACLE);
    ObjectFactory::CreateComponent<SpriteRenderer>(build, sprite);

    AABBCollider* resCollider = ObjectFactory::CreateComponent<AABBCollider>(build, -80, -80, 80, 80);
    resCollider->SetTrigger(false);
    resCollider->SetStatic(true);
}