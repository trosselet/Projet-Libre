#ifndef INVENTORY_INCLUDE
#define INVENTORY_INCLUDE

#include "scripts/Script.h"

#include <map>

#include "ECS/Components/ui/Text.h"

class Image;

enum class BonusType : int32_t
{
	NONE_BONUS,
	SLOWSPEED,
	BIGGERCIRCLE,
	EFFICIENCY,
	INCREASEHP,

	COUNT_BONUS

};

enum class MalusType : int32_t
{
	NONE_MALUS,
	FASTSPEED,
	SMALLERCIRCLE,
	INEFFICIENCY,
	DECREASEHP,

	COUNT_MALUS
};

enum Material : int32_t
{
	WOOD_BASIC,
	WOOD_DARK_OAK,
	WOOD_PALM,
	PLANK_BASIC,
	PLANK_DARK_OAK,
	PLANK_PALM_WOOD,
	STONE,
	REFINED_STONE,
	COAL,
	COPPER,
	COPPER_INGOT,
	IRON,
	IRON_INGOT,
	STEEL,

	WOODEN_SWORD,
	SHARP_WOOD_SWORD,
	ENCHANTED_SWORD,

	STONE_SWORD,
	IRON_SWORD,
	REFINED_IRON_KATANA,

	REFINED_STEEL_SWORD,
	HEAVY_WOOD_SWORD,
	CARBON_STEEL_SWORD,

	LIVING_WOOD_STEEL_SWORD,

	GRAIN_LEATHER_HELMET,
	GRAIN_LEATHER_BREASTPLATE,
	GRAIN_LEATHER_PANTS,
	GRAIN_LEATHER_BOOTS,

	TOP_GRAIN_LEATHER_HELMET,
	TOP_GRAIN_LEATHER_BREASTPLATE,
	TOP_GRAIN_LEATHER_PANTS,
	TOP_GRAIN_LEATHER_BOOTS,

	RUSTY_HELMET,
	RUSTY_BREASTPLATE,
	RUSTY_PANTS,
	RUSTY_BOOTS,

	CHAINMAIL_HELMET,
	CHAINMAIL_BREASTPLATE,
	CHAINMAIL_PANTS,
	CHAINMAIL_BOOTS,

	IRON_HELMET,
	IRON_BREASTPLATE,
	IRON_PANTS,
	IRON_BOOTS,

	GOLD_HELMET,
	GOLD_BREASTPLATE,
	GOLD_PANTS,
	GOLD_BOOTS,

	COUNT_ITEM
};

enum ItemType  : uint8_t
{
	HELMET,
	CHESTPLATE,
	PANTS,
	BOOTS,
	ITEM,
	SWORD,
	WEAPON_2,

	COUNT_TYPE
};

struct Item 
{
	unsigned int type;
	unsigned int id;
	std::string name;
	unsigned int actualCount = 0;
	unsigned int maxCount = 0;
	bool isActive = false;
	Sprite* sprite;
	std::map<MalusType, float> malus;
	std::map<BonusType, float> bonuses;
};

struct Armor {
	Item item;
	unsigned int defense;
	unsigned int durability;
	Image* uiImage;
	Text* text;
};

class Inventory : public IScript
{
public:

	float zoom = 0.65f;
	
	Inventory();
	~Inventory() = default;
	
	void OnStart() override;
	void OnUpdate() override;
	void OnRender(RenderWindow* window) override;

	void AddItem(const Item& id);
	void AddItemCount(int id, unsigned int amount);
	void RemoveItemCount(int id, unsigned int amount);

	unsigned int GetItemCount(int id);
	bool HasEnough(int id, unsigned int amount);

	void DisplayInventory();
	void CloseInventory();

	unsigned int CalculateArmorStats();

	std::map<Material, Item> Items;
	std::map<unsigned int, Armor> Armors;

private:
	void UpdateItemState(int id);
	
	sf::Text* mCaseText;
	std::map<Material, Text*> mItemsText;

	std::vector<Image*> mSlots;
	Entity* mInventory;
	Entity* mTitle;
};


#endif // !INVENTORY_INCLUDE