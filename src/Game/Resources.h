#pragma once

class Sprite;

class Resources
{
public:
    Resources() = default;
    ~Resources();
    
    void Initialize();
    void CreateShaders();
    void CreateParticles();
    void CreateTextures();
    void CreateSprite();
    void CreateFonts();
    
    static Resources& instance()
    {
        static Resources instance;
        return instance;
    }

    ////////////////////////////////
    /////// SHADERS

    Shader* BLUR_SHADER;
    
    ////////////////////////////////
    /////// TEXTURES

    Texture* SPRITE_SHEET;
    Texture* DEFAULT_TEXTURE;
    Texture* TEXTURE_INVENTORY;
    Texture* TEXTURE_BUTTON;
    Texture* TEXTURE_QUEST;
    
    Texture* TEXTURE_HEALTH_BAR;
    Texture* TEXTURE_HEALTH_BACKGROUND;
    Texture* TEXTURE_BOX;
    Texture* TEXTURE_HOTKEY;
    Texture* TEXTURE_ITEMBOX;
    
    Texture* TEXTURE_RESOURCES;
    Texture* TEXTURE_ARMOR_WEAPON;
    Texture* TEXTURE_UI_TITLE_CONTAINER;

	Texture* TEXTURE_WORKBENCH;
	Texture* TEXTURE_FURNACE;
	Texture* TEXTURE_ANVIL;

	Texture* TEXTURE_CIRCLE1;
	Texture* TEXTURE_CIRCLE2;
	Texture* TEXTURE_MAINCIRCLE;
	Texture* TEXTURE_BARRE;

	Texture* BUILDING_BLUE;
	Texture* BUILDING_BLUE2;
	Texture* BUILDING_GREEN;
	Texture* BUILDING_GREEN2;
	Texture* BUILDING_SHOP;
	Texture* BUILDING_MEDIC;

    Texture* IDLE_PLAYER_TEXTURE;
    Texture* WALK_PLAYER_TEXTURE;
    Texture* IDLE_EVIL_EYE_TEXTURE;
    Texture* ATTACK_EVIL_EYE_TEXTURE;
    Texture* IDLE_FROST_GUARDIAN_TEXTURE;
    Texture* ATTACK_FROST_GUARDIAN_TEXTURE;
    Texture* IDLE_GROLUX_TEXTURE;
    Texture* ATTACK_GROLUX_TEXTURE;

	Texture* TEXTURE_BACKGROUND;
    
    
    ////////////////////////////////
    /////// SPRITES

    Sprite* DEFAULT_SPRITE;
    Sprite* DEFAULT_PLAYER_SPRITE;
    Sprite* DEFAULT_MONSTER_SPRITE;
    
    Sprite* INVENTORY;
    Sprite* BUTTON;
    Sprite* QUEST;
    Sprite* HEALTH_BAR;
    Sprite* BACKGROUND_HEALTH_BAR;
    
    Sprite* UI_TITLE_CONTAINER;
    
    Sprite* RESOURCE_BASIC_WOOD;
    Sprite* RESOURCE_BASIC_PLANK;
    Sprite* RESOURCE_DARK_OAK_WOOD;
    Sprite* RESOURCE_DARK_OAK_PLANK;
    Sprite* RESOURCE_PALM_WOOD;
    Sprite* RESOURCE_PALM_PLANK;
    Sprite* RESOURCE_COAL;
    Sprite* RESOURCE_STONE;
    Sprite* RESOURCE_REFINED_STONE;
    Sprite* RESOURCE_COPPER;
    Sprite* RESOURCE_COPPER_INGOT;
    Sprite* RESOURCE_IRON;
    Sprite* RESOURCE_IRON_INGOT;
    Sprite* RESOURCE_STEEL;
	Sprite* RESOURCE_WOODEN_SWORD;
	Sprite* RESOURCE_SHARP_WOOD_SWORD;
	Sprite* RESOURCE_ENCHANTED_SWORD;
	Sprite* RESOURCE_STONE_SWORD;
	Sprite* RESOURCE_IRON_SWORD;
	Sprite* RESOURCE_REFINED_IRON_KATANA;
	Sprite* RESOURCE_REFINED_STEEL_SWORD;
	Sprite* RESOURCE_HEAVY_WOOD_SWORD;
	Sprite* RESOURCE_CARBON_STEEL_SWORD;
	Sprite* RESOURCE_LIVING_WOOD_STEEL_SWORD;
	Sprite* RESOURCE_GRAIN_LEATHER_HELMET;
	Sprite* RESOURCE_GRAIN_LEATHER_BREASTPLATE;
	Sprite* RESOURCE_GRAIN_LEATHER_PANTS;
	Sprite* RESOURCE_GRAIN_LEATHER_BOOTS;
	Sprite* RESOURCE_TOP_GRAIN_LEATHER_HELMET;
	Sprite* RESOURCE_TOP_GRAIN_LEATHER_BREASTPLATE;
	Sprite* RESOURCE_TOP_GRAIN_LEATHER_PANTS;
	Sprite* RESOURCE_TOP_GRAIN_LEATHER_BOOTS;
	Sprite* RESOURCE_RUSTY_HELMET;
	Sprite* RESOURCE_RUSTY_BREASTPLATE;
	Sprite* RESOURCE_RUSTY_PANTS;
	Sprite* RESOURCE_RUSTY_BOOTS;
	Sprite* RESOURCE_CHAINMAIL_HELMET;
	Sprite* RESOURCE_CHAINMAIL_BREASTPLATE;
	Sprite* RESOURCE_CHAINMAIL_PANTS;
	Sprite* RESOURCE_CHAINMAIL_BOOTS;
	Sprite* RESOURCE_IRON_HELMET;
	Sprite* RESOURCE_IRON_BREASTPLATE;
	Sprite* RESOURCE_IRON_PANTS;
	Sprite* RESOURCE_IRON_BOOTS;
	Sprite* RESOURCE_GOLD_HELMET;
	Sprite* RESOURCE_GOLD_BREASTPLATE;
	Sprite* RESOURCE_GOLD_PANTS;
	Sprite* RESOURCE_GOLD_BOOTS;
    
    Sprite* WORKSTATION;
    Sprite* ITEMBOX;

	Sprite* HITCIRCLE1;
	Sprite* HITCIRCLE2;
	Sprite* MAINCIRCLE;
	Sprite* BARRE;

    Sprite* RESOURCE_BUILDING_BLUE;
	Sprite* RESOURCE_BUILDING_BLUE2;
	Sprite* RESOURCE_BUILDING_GREEN;
    Sprite* RESOURCE_BUILDING_GREEN2;
	Sprite* RESOURCE_BUILDING_SHOP;
	Sprite* RESOURCE_BUILDING_MEDIC;

    Sprite* RESOURCE_BACKGROUND;

    ////////////////////////////////
    /////// FONTS

    sf::Font* DEFAULT_FONT;

	////////////////////////////////
	/////// SPRITES SHEETS
	SpriteSheet* FURNACE;
	SpriteSheet* ANVIL;

	SpriteSheet* PLAYER_IDLE;
	SpriteSheet* PLAYER_WALK;
	SpriteSheet* EVIL_EYE_IDLE;
	SpriteSheet* EVIL_EYE_ATTACK;
	SpriteSheet* FROST_GUARDIAN_IDLE;
	SpriteSheet* FROST_GUARDIAN_ATTACK;
    SpriteSheet* GROLUX_IDLE;
	SpriteSheet* GROLUX_ATTACK;

};
