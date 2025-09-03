#include "pch.h"
#include "Inventory.h"

#include "ObjectFactory.h"
#include "ECS/Components/ui/Image.h"
#include "ECS/Components/ui/Text.h"

Inventory::Inventory() : mCaseText(nullptr), mInventory(nullptr), mTitle(nullptr)
{
	Items =
	{
		{WOOD_BASIC, Item{ITEM, WOOD_BASIC, "Bois", 0, 100, false, Resources::instance().RESOURCE_BASIC_WOOD, {}, {}}},
		{
			WOOD_DARK_OAK,
			Item{ITEM, WOOD_DARK_OAK, "Bois Noir", 0, 100, false, Resources::instance().RESOURCE_DARK_OAK_WOOD, {}, {}}
		},
		{
			WOOD_PALM,
			Item{ITEM, WOOD_PALM, "Bois de palme", 0, 100, false, Resources::instance().RESOURCE_PALM_WOOD, {}, {}}
		},
		{
			PLANK_BASIC,
			Item{ITEM, PLANK_BASIC, "Planche", 0, 100, false, Resources::instance().RESOURCE_BASIC_PLANK, {}, {}}
		},
		{
			PLANK_PALM_WOOD,
			Item{
				ITEM, PLANK_PALM_WOOD, "Planche Noire", 0, 100, false, Resources::instance().RESOURCE_PALM_PLANK, {}, {}
			}
		},
		{
			PLANK_DARK_OAK,
			Item{
				ITEM, PLANK_DARK_OAK, "Planche de palme", 0, 100, false, Resources::instance().RESOURCE_DARK_OAK_PLANK,
				{}, {}
			}
		},
		{ STONE						, Item{ITEM, STONE, "Pierre",0, 100, false, Resources::instance().RESOURCE_STONE	} },
		{ REFINED_STONE					, Item{ITEM, REFINED_STONE, "Pierre Rafinee",0, 100, false, Resources::instance().RESOURCE_REFINED_STONE } },
		{ COAL							, Item{ITEM, COAL, "Charbon",0, 40, false, Resources::instance().RESOURCE_COAL	} },
		{ COPPER						, Item{ITEM, COPPER, "Cuivre",0, 50, false, Resources::instance().RESOURCE_COPPER	} },
		{ COPPER_INGOT					, Item{ITEM, COPPER_INGOT, "Lingot de Cuivre",0, 50, false, Resources::instance().RESOURCE_COPPER_INGOT } },
		{ IRON							, Item{ITEM, IRON, "Fer",0, 50, false, Resources::instance().RESOURCE_IRON	} },
		{ IRON_INGOT					, Item{ITEM, IRON_INGOT, "Lingot de Fer",0, 50, false, Resources::instance().RESOURCE_IRON_INGOT	} },
		{ STEEL 						, Item{ITEM, STEEL, "Acier",0, 40, false, Resources::instance().RESOURCE_STEEL	} },
		{ WOODEN_SWORD					, Item{SWORD, WOODEN_SWORD, "Epee en bois", 0, 1, false, Resources::instance().RESOURCE_WOODEN_SWORD }	},
		{ SHARP_WOOD_SWORD				, Item{SWORD, SHARP_WOOD_SWORD, "Epee aiguisee", 0, 1, false, Resources::instance().RESOURCE_SHARP_WOOD_SWORD }	},
		{ ENCHANTED_SWORD				, Item{SWORD, ENCHANTED_SWORD, "Epee enchantee", 0, 1, false, Resources::instance().RESOURCE_ENCHANTED_SWORD }	},
		{ STONE_SWORD					, Item{SWORD, STONE_SWORD, "Epee en silex", 0, 1, false, Resources::instance().RESOURCE_STONE_SWORD }	},
		{ IRON_SWORD					, Item{SWORD, IRON_SWORD, "Epee en fer", 0, 1, false, Resources::instance().RESOURCE_IRON_SWORD }	},
		{ REFINED_IRON_KATANA			, Item{SWORD, REFINED_IRON_KATANA, "Katana en fer", 0, 1, false, Resources::instance().RESOURCE_REFINED_IRON_KATANA }	},
		{ REFINED_STEEL_SWORD			, Item{SWORD, REFINED_STEEL_SWORD, "Epee en acier", 0, 1, false, Resources::instance().RESOURCE_REFINED_STEEL_SWORD }	},
		{ HEAVY_WOOD_SWORD				, Item{SWORD, HEAVY_WOOD_SWORD, "Epee à deux mains", 0, 1, false, Resources::instance().RESOURCE_HEAVY_WOOD_SWORD }	},
		{ CARBON_STEEL_SWORD			, Item{SWORD, CARBON_STEEL_SWORD, "Dague en carbon", 0, 1, false, Resources::instance().RESOURCE_CARBON_STEEL_SWORD }	},
		{ LIVING_WOOD_STEEL_SWORD		, Item{SWORD, LIVING_WOOD_STEEL_SWORD, "Epee en bois vivant", 0, 1, false, Resources::instance().RESOURCE_LIVING_WOOD_STEEL_SWORD }	},
		{ GRAIN_LEATHER_HELMET			, Item{HELMET, GRAIN_LEATHER_HELMET, "Chapeau en cuir", 0, 1, false, Resources::instance().RESOURCE_GRAIN_LEATHER_HELMET }	},
		{ GRAIN_LEATHER_BREASTPLATE		, Item{CHESTPLATE, GRAIN_LEATHER_BREASTPLATE, "Veste en cuir", 0, 1, false, Resources::instance().RESOURCE_GRAIN_LEATHER_BREASTPLATE }	},
		{ GRAIN_LEATHER_PANTS			, Item{PANTS, GRAIN_LEATHER_PANTS, "Short en cuir", 0, 1, false, Resources::instance().RESOURCE_GRAIN_LEATHER_PANTS }	},
		{ GRAIN_LEATHER_BOOTS			, Item{BOOTS, GRAIN_LEATHER_BOOTS, "Bottes en cuir", 0, 1, false, Resources::instance().RESOURCE_GRAIN_LEATHER_BOOTS }	},
		{ TOP_GRAIN_LEATHER_HELMET		, Item{HELMET, TOP_GRAIN_LEATHER_HELMET, "Casque en cuir", 0, 1, false, Resources::instance().RESOURCE_TOP_GRAIN_LEATHER_HELMET }	},
		{ TOP_GRAIN_LEATHER_BREASTPLATE	, Item{CHESTPLATE, TOP_GRAIN_LEATHER_BREASTPLATE, "Plastron en cuir", 0, 1, false, Resources::instance().RESOURCE_TOP_GRAIN_LEATHER_BREASTPLATE }	},
		{ TOP_GRAIN_LEATHER_PANTS		, Item{PANTS, TOP_GRAIN_LEATHER_PANTS, "Pantalon en cuir", 0, 1, false, Resources::instance().RESOURCE_TOP_GRAIN_LEATHER_PANTS }	},
		{ TOP_GRAIN_LEATHER_BOOTS		, Item{BOOTS, TOP_GRAIN_LEATHER_BOOTS, "Cuissarde en cuir", 0, 1, false, Resources::instance().RESOURCE_TOP_GRAIN_LEATHER_BOOTS }	},
		{ RUSTY_HELMET					, Item{HELMET, RUSTY_HELMET, "Casque rouille", 0, 1, false, Resources::instance().RESOURCE_RUSTY_HELMET }	},
		{ RUSTY_BREASTPLATE				, Item{CHESTPLATE, RUSTY_BREASTPLATE, "Plastron rouille", 0, 1, false, Resources::instance().RESOURCE_RUSTY_BREASTPLATE }	},
		{ RUSTY_PANTS					, Item{PANTS, RUSTY_PANTS, "Pantalon rouille", 0, 1, false, Resources::instance().RESOURCE_RUSTY_PANTS }	},
		{ RUSTY_BOOTS					, Item{BOOTS, RUSTY_BOOTS, "Bottes rouille", 0, 1, false, Resources::instance().RESOURCE_RUSTY_BOOTS }	},
		{ CHAINMAIL_HELMET				, Item{HELMET, CHAINMAIL_HELMET, "Casque de mailles", 0, 1, false, Resources::instance().RESOURCE_CHAINMAIL_HELMET }	},
		{ CHAINMAIL_BREASTPLATE			, Item{CHESTPLATE, CHAINMAIL_BREASTPLATE, "Plastron de mailles", 0, 1, false, Resources::instance().RESOURCE_CHAINMAIL_BREASTPLATE }	},
		{ CHAINMAIL_PANTS				, Item{PANTS, CHAINMAIL_PANTS, "Pantalon de mailles", 0, 1, false, Resources::instance().RESOURCE_CHAINMAIL_PANTS }	},
		{ CHAINMAIL_BOOTS				, Item{BOOTS, CHAINMAIL_BOOTS, "Bottes de mailles", 0, 1, false, Resources::instance().RESOURCE_CHAINMAIL_BOOTS }	},
		{ IRON_HELMET					, Item{HELMET, IRON_HELMET, "Casque en fer", 0, 1, false, Resources::instance().RESOURCE_IRON_HELMET }	},
		{ IRON_BREASTPLATE				, Item{CHESTPLATE, IRON_BREASTPLATE, "Plastron en fer", 0, 1, false, Resources::instance().RESOURCE_IRON_BREASTPLATE }	},
		{ IRON_PANTS					, Item{PANTS, IRON_PANTS, "Pantalon en fer", 0, 1, false, Resources::instance().RESOURCE_IRON_PANTS }	},
		{ IRON_BOOTS					, Item{BOOTS, IRON_BOOTS, "Bottes en fer", 0, 1, false, Resources::instance().RESOURCE_IRON_BOOTS }	},
		{ GOLD_HELMET					, Item{HELMET, GOLD_HELMET, "Casque en fer", 0, 1, false, Resources::instance().RESOURCE_GOLD_HELMET }	},
		{ GOLD_BREASTPLATE				, Item{CHESTPLATE, GOLD_BREASTPLATE, "Plastron en fer", 0, 1, false, Resources::instance().RESOURCE_GOLD_BREASTPLATE }	},
		{ GOLD_PANTS					, Item{PANTS, GOLD_PANTS, "Pantalon en or", 0, 1, false, Resources::instance().RESOURCE_GOLD_PANTS }	},
		{ GOLD_BOOTS					, Item{BOOTS, GOLD_BOOTS, "Bottes en or", 0, 1, false, Resources::instance().RESOURCE_GOLD_BOOTS }	},
	};

	Armors =  {};
}

void Inventory::OnStart()
{
	float baseX = 1500;
	float baseY = 500;

	mCaseText = new sf::Text(*Resources::instance().DEFAULT_FONT, "", 15 * zoom);

	mItemsText.clear();
	mSlots.clear();

	mInventory = ObjectFactory::CreateEntity<Entity>(0);
	ObjectFactory::CreateComponent<Image>(mInventory, Resources::instance().INVENTORY, sf::Vector2f(baseX, baseY), sf::Vector2f(5.0f, 5.0f));

	mTitle = ObjectFactory::CreateEntity<Entity>(mInventory, 1);
	ObjectFactory::CreateComponent<Image>(mTitle,
		Resources::instance().UI_TITLE_CONTAINER, sf::Vector2f(baseX + 175.0f, baseY - 30.0f), sf::Vector2f(3.0f, 3.0f));
	ObjectFactory::CreateComponent<Text>(mTitle,
		Resources::instance().DEFAULT_FONT, 20, "Inventaire", sf::Vector2f(baseX + 200.0f, baseY - 26.0f));

	int i = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			Entity* slot = ObjectFactory::CreateEntity<Entity>(mInventory, 1);
			Image* image = ObjectFactory::CreateComponent<Image>(slot, Resources::instance().ITEMBOX,
				sf::Vector2f(baseX + 100.0f + 60.0f * x, baseY + 100.0f + 60.0f * y), sf::Vector2f(2.0f, 2.0f));

			if (i < Items.size())
			{
				Item item = Items[static_cast<Material>(i)];
				if (item.type != ItemType::ITEM) continue;
				Entity* content = ObjectFactory::CreateEntity<Entity>(slot, 2);
				Image* image = ObjectFactory::CreateComponent<Image>(content, item.sprite,
					sf::Vector2f(baseX + 105.0f + 60.0f * x, baseY + 105.0f + 60.0f * y), sf::Vector2f(1.5f, 1.5f));
				mItemsText.emplace(static_cast<Material>(i), ObjectFactory::CreateComponent<Text>(content, Resources::instance().DEFAULT_FONT, 12, std::to_string(item.actualCount),
					sf::Vector2f(baseX + 100.0f + 60.0f * x, baseY + 100.0f + 60.0f * y)));
			}
			i++;
			mSlots.push_back(image);
		}
	}

	if (Armors.empty())
	{
		Armors.emplace(0, Items[GRAIN_LEATHER_HELMET]);
		Armors.emplace(1, Items[TOP_GRAIN_LEATHER_BREASTPLATE]);
		Armors.emplace(2, Items[TOP_GRAIN_LEATHER_PANTS]);
		Armors.emplace(3, Items[GRAIN_LEATHER_PANTS]);
		Armors.emplace(4, Items[WOODEN_SWORD]);
		Armors.emplace(5, Items[WOODEN_SWORD]);
	}

	for (int i = 0; i < 4; i++)
	{
		Armor& armor = Armors[i];
		// Armor
		Entity* ArmorSlot = ObjectFactory::CreateEntity<Entity>(mInventory, 1);
		Image* armorImage = ObjectFactory::CreateComponent<Image>(ArmorSlot, Resources::instance().ITEMBOX, sf::Vector2f(2000, 610 + i * 125), sf::Vector2f(3.0f, 3.0f));
		Text* armorText = ObjectFactory::CreateComponent<Text>(ArmorSlot, Resources::instance().DEFAULT_FONT, 14, "", sf::Vector2f(1950, 580 + i * 125));
		
		Entity* displayArmor = ObjectFactory::CreateEntity<Entity>(mInventory, 2);
		Image* displayImage = ObjectFactory::CreateComponent<Image>(displayArmor, Resources::instance().ITEMBOX, sf::Vector2f(2000, 610 + i * 125), sf::Vector2f(2.0f, 2.0f));

		armor.text = armorText;
		armor.uiImage = displayImage;
		mSlots.push_back(armorImage);
	}

	for (int i = 0; i < 2; i++)
	{
		// Sword / Item
		Armor& armor = Armors[4+i];
		Entity* ItemSlot = ObjectFactory::CreateEntity<Entity>(mInventory);
		Image* ItemImage = ObjectFactory::CreateComponent<Image>(ItemSlot, Resources::instance().ITEMBOX, sf::Vector2f(1600, 885 + i * 100), sf::Vector2f(3.0f, 3.0f));
		Text* armorText = ObjectFactory::CreateComponent<Text>(ItemSlot, Resources::instance().DEFAULT_FONT, 14, "", sf::Vector2f(1600, 855 + i * 100));

		Entity* displaySword = ObjectFactory::CreateEntity<Entity>(mInventory);
		Image* displayImage = ObjectFactory::CreateComponent<Image>(displaySword, Resources::instance().ITEMBOX, sf::Vector2f(1600, 885 + i * 100), sf::Vector2f(2.0f, 2.0f));

		armor.text = armorText;
		armor.uiImage = displayImage;
		
		mSlots.push_back(ItemImage);
	}

	mInventory->SetEnabled(false);
}

void Inventory::OnUpdate()
{
	if (!mInventory) return;
	if (mInventory->IsEnable())
	{
		for (auto& materialText : mItemsText)
		{
			materialText.second->WriteText->setString(std::to_string(GetItemCount(materialText.first)));
		}

		for (auto& [id, armor] : Armors)
		{
			armor.text->WriteText->setString(armor.item.name);
			armor.uiImage->UIImage = armor.item.sprite;
		}
	}

	if (GetKeyDown(Keyboard::E))
	{
		Debug::Log("Open;");
		mInventory->SetEnabled(!mInventory->IsEnable());
	}
}


void Inventory::OnRender(RenderWindow* window)
{

}

void Inventory::AddItem(const Item& item)
{
	switch (item.type)
	{
	case ItemType::ITEM:
		{
			Items[static_cast<Material>(item.id)].actualCount = item.actualCount;
		}
	case ItemType::SWORD:
		{
			
		}
	default:
		{
			Armors[item.type].item = item;
		}
	}
}

void Inventory::AddItemCount(int id, unsigned int amount)
{
	if (id < 0 || id >= Items.size())
	{
		Debug::Log("The id: " + std::to_string(id) + " is not in the range of the inventory");
		return;
	}

	Item& item = Items[static_cast<Material>(id)];
	if (item.actualCount + amount <= item.maxCount)
	{
		item.actualCount += amount;
	}
	else
	{
		item.actualCount = item.maxCount;
	}

	UpdateItemState(id);
	Debug::Log("The item: " + std::to_string(item.id) + " increased by " + std::to_string(amount) + ", new quantity = " + std::to_string(item.actualCount));
}

void Inventory::RemoveItemCount(int id, unsigned int amount)
{
	if (id < 0 || id >= Items.size())
	{
		Debug::Log("The id: " + std::to_string(id) + " is not in the range of the inventory");
		return;
	}

	Item& item = Items[static_cast<Material>(id)];
	if (item.actualCount >= amount)
	{
		item.actualCount -= amount;
	}
	else
	{
		item.actualCount = 0;
	}

	UpdateItemState(id);
	Debug::Log("The item: " + std::to_string(item.id) + " decreased, new quantity = " + std::to_string(item.actualCount));
}

void Inventory::UpdateItemState(int id)
{
	if (id < 0 || id >= Items.size())
	{
		return;
	}

	Items[static_cast<Material>(id)].isActive = (Items[static_cast<Material>(id)].actualCount > 0);
}

unsigned int Inventory::GetItemCount(int id)
{
	if (id < 0 || id >= Items.size())
	{
		Debug::Log("The id: " + std::to_string(id) + " is not in the range of the inventory");
		return 0;
	}

	return Items[static_cast<Material>(id)].actualCount;
}

bool Inventory::HasEnough(int id, unsigned int amount)
{
	return Items[static_cast<Material>(id)].actualCount >= amount;
}

void Inventory::DisplayInventory()
{
	mInventory->SetEnabled(true);

	Debug::Log("===== INVENTORY START =====");

	for (auto& [material, item] : Items)
	{
		if (item.actualCount > 0)
		{
			Debug::Log("Item ID: " + std::to_string(item.id));
			Debug::Log("Actual Count: " + std::to_string(item.actualCount));
			Debug::Log("Max Count: " + std::to_string(item.maxCount));
			Debug::Log("Is Active: " + std::string(item.isActive ? "Yes" : "No"));
			Debug::Log("----------------------");
		}
	}
	Debug::Log("====== INVENTORY END ======");
}

void Inventory::CloseInventory()
{
	mInventory->SetEnabled(false);
}

unsigned int Inventory::CalculateArmorStats()
{
	unsigned int totalDefense = 0;
	unsigned int totalDurability = 0;

	for (const auto& [id, armor] : Armors)
	{
		totalDefense += armor.defense;
		totalDurability += armor.durability;
	}

	Debug::Log("Total Defense: " + std::to_string(totalDefense));
	Debug::Log("Total Durability: " + std::to_string(totalDurability));

	return totalDefense;
}

