#include "pch.h"
#include "../Editor.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Tilemap.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/ui/Button.h"
#include "scripts/interact/InteractCraftingStation.h"
#include "scripts/resources/Craft.h"
#include "scripts/tilemap/TilemapEditor.h"

void Editor::OnEnter()
{

    Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
    
    ObjectFactory::AttachScript<TilemapEditor>(gridContainer,
        "../../res/Tiles/tileset.png",
        "../../res/Tiles/tileset.png",
        "../../res/Tiles/saved/house1.txt");
    
    Entity* camera = ObjectFactory::CreateEntity<Entity>(gridContainer);
    ObjectFactory::CreateComponent<Camera>(camera);
    
}