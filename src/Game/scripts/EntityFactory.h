#pragma once

class ResourceInteraction;
class MusicScript;
class PlayerMovement;
class Entity;
struct LootTable;
class Inventory;

class EntityFactory
{
public:
    static ResourceInteraction* CreateResource(MusicScript* music, Entity* player, PlayerMovement* playerMovement, Inventory* inventory, LootTable lootTable, float x, float y, float sizeX, float sizeY, int beatmap);
    static void CreateBuilding(int x, int y, Sprite* sprite);
};
