#include "pch.h"
#include "Resources.h"

#include "SpriteSheet.h"
#include "Render/Sprite.h"
#include "Render/Texture.h"

Resources::~Resources()
{
}

void Resources::Initialize()
{
    Resources* resources = &instance();
    
    resources->CreateShaders();
    resources->CreateParticles();
    resources->CreateTextures();
    resources->CreateSprite();
    resources->CreateFonts();
}

void Resources::CreateShaders()
{
	BLUR_SHADER = new Shader(L"blur.frag", Shader::Type::Fragment);
	BLUR_SHADER->setUniform("blur_radius", 50.0f);
    /*DEFAULT_SHADER_VERT = new Shader(L"Particles/particles.vert", Shader::Type::Vertex);
    DEFAULT_SHADER_FRAG = new Shader(L"Particles/particles.frag", Shader::Type::Fragment);*/
}

void Resources::CreateParticles()
{
}

void Resources::CreateTextures()
{
    SPRITE_SHEET = new Texture("../../res/Tiles/tileset.png", false);
    DEFAULT_TEXTURE =           new Texture("default.png");
    IDLE_PLAYER_TEXTURE =    new Texture("../../res/Textures/player/Idle.png");
    WALK_PLAYER_TEXTURE =    new Texture("../../res/Textures/player/Run.png");
    IDLE_EVIL_EYE_TEXTURE =   new Texture("../../res/Textures/Monsters/EvilEye/Idle/sprite_sheet.png");
    ATTACK_EVIL_EYE_TEXTURE =   new Texture("../../res/Textures/Monsters/EvilEye/Attack/spritesheet.png");
    IDLE_FROST_GUARDIAN_TEXTURE =   new Texture("../../res/Textures/Monsters/FrostGuardian/Idle/spritesheet.png");
    ATTACK_FROST_GUARDIAN_TEXTURE =   new Texture("../../res/Textures/Monsters/FrostGuardian/Attack/spritesheet.png");
    IDLE_GROLUX_TEXTURE = new Texture("../../res/Textures/Monsters/Golux/Idle.png");
    ATTACK_GROLUX_TEXTURE = new Texture("../../res/Textures/Monsters/Golux/AttackA.png");

    TEXTURE_QUEST =         new Texture("QuestUI.png");
    TEXTURE_INVENTORY =         new Texture("Inventory.png");
    TEXTURE_BUTTON =         new Texture("button.png");
    TEXTURE_HEALTH_BAR =        new Texture("bar.png");
    TEXTURE_HEALTH_BACKGROUND = new Texture("ui_background.png");
    TEXTURE_BOX =               new Texture("ui_box.png");
    TEXTURE_HOTKEY =            new Texture("hotkey.png");
    TEXTURE_ITEMBOX =           new Texture("itembox.png");
    TEXTURE_RESOURCES =         new Texture("resources.png");
    TEXTURE_ARMOR_WEAPON =         new Texture("armors.png");
    TEXTURE_UI_TITLE_CONTAINER =new Texture("titlebox.png");
    TEXTURE_CIRCLE1 = new Texture("../../res/Textures/MusicGame/HITCIRCLE1.png");
    TEXTURE_CIRCLE2 = new Texture("../../res/Textures/MusicGame/HITCIRCLE2.png");
	TEXTURE_MAINCIRCLE = new Texture("../../res/Textures/MusicGame/CIRCLE.png");
    TEXTURE_BARRE = new Texture("../../res/Textures/MusicGame/BARRE.png");

	BUILDING_BLUE = new Texture("../../res/Textures/BUILDING_BLUE.png");
	BUILDING_BLUE2 = new Texture("../../res/Textures/BUILDING_BLUE2.png");
	BUILDING_GREEN = new Texture("../../res/Textures/BUILDING_GREEN.png");
	BUILDING_GREEN2 = new Texture("../../res/Textures/BUILDING_GREEN2.png");
	BUILDING_SHOP = new Texture("../../res/Textures/BUILDING_SHOP.png");
	BUILDING_MEDIC = new Texture("../../res/Textures/BUILDING_MEDIC.png");
    
    TEXTURE_WORKBENCH =         new Texture("Stations/Workbench/Workbench.png");
    TEXTURE_FURNACE =         new Texture("Stations/Furnace/Iron_03-Sheet.png");
    TEXTURE_ANVIL =         new Texture("Stations/Anvil/Anvil_01-Sheet.png");

    TEXTURE_BACKGROUND = new Texture("../../res/Textures/black.png");
}

void Resources::CreateSprite()
{
    DEFAULT_SPRITE =        new Sprite(*DEFAULT_TEXTURE);
    DEFAULT_PLAYER_SPRITE =        new Sprite(*IDLE_PLAYER_TEXTURE);
    DEFAULT_MONSTER_SPRITE =        new Sprite(*IDLE_EVIL_EYE_TEXTURE);

    INVENTORY =             new Sprite(*TEXTURE_INVENTORY);
    BUTTON =				new Sprite(*TEXTURE_BUTTON);
    QUEST =                 new Sprite(*TEXTURE_QUEST);
    
    HEALTH_BAR =            new Sprite(*TEXTURE_HEALTH_BAR);
    BACKGROUND_HEALTH_BAR = new Sprite(*TEXTURE_HEALTH_BACKGROUND);

    UI_TITLE_CONTAINER =    new Sprite(*TEXTURE_UI_TITLE_CONTAINER);

    RESOURCE_BASIC_WOOD     = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {0, 0}, {24, 24});
    RESOURCE_BASIC_PLANK    = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {24, 0}, {24, 24});
    RESOURCE_DARK_OAK_WOOD  = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {144, 0}, {24, 24});
    RESOURCE_DARK_OAK_PLANK = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {168, 0}, {24, 24});
    RESOURCE_PALM_WOOD      = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {192, 0}, {24, 24});
    RESOURCE_PALM_PLANK     = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {216, 0}, {24, 24});

    RESOURCE_COAL           = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {96, 0}, {24, 24});
    RESOURCE_STONE          = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {24, 24}, {24, 24});
    RESOURCE_REFINED_STONE  = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {192, 24}, {24, 24});
    RESOURCE_IRON           = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {192, 72}, {24, 24});
    RESOURCE_IRON_INGOT     = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {192, 120}, {24, 24});
    RESOURCE_COPPER         = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {48, 72}, {24, 24});
    RESOURCE_COPPER_INGOT   = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {48, 120}, {24, 24});
    RESOURCE_STEEL          = new Sprite(*TEXTURE_RESOURCES, sf::Vector2f(1.5f, 1.5f), {72, 120}, {24, 24});

    RESOURCE_WOODEN_SWORD =                   new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {0, 128}, {32, 32});
    RESOURCE_SHARP_WOOD_SWORD =               new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {32, 128}, {32, 32});
    RESOURCE_ENCHANTED_SWORD =                new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {64, 128}, {32, 32});
    RESOURCE_STONE_SWORD =                    new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {96, 128}, {32, 32});
    RESOURCE_IRON_SWORD =                     new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {0, 0}, {32, 32});
    RESOURCE_REFINED_IRON_KATANA =            new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {32, 0}, {32, 32});
    RESOURCE_REFINED_STEEL_SWORD =            new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {64, 0}, {32, 32});
    RESOURCE_HEAVY_WOOD_SWORD =               new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {96, 0}, {32, 32});
    RESOURCE_CARBON_STEEL_SWORD =             new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {128, 0}, {32, 32});
    RESOURCE_LIVING_WOOD_STEEL_SWORD =        new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {160, 0}, {32, 32});
    RESOURCE_GRAIN_LEATHER_HELMET =           new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {32, 256}, {32, 32});
    RESOURCE_GRAIN_LEATHER_BREASTPLATE =      new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {32, 288}, {32, 32});
    RESOURCE_GRAIN_LEATHER_PANTS =            new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {32, 320}, {32, 32});
    RESOURCE_GRAIN_LEATHER_BOOTS =            new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {32, 352}, {32, 32});
    RESOURCE_TOP_GRAIN_LEATHER_HELMET =       new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {64, 256}, {32, 32});
    RESOURCE_TOP_GRAIN_LEATHER_BREASTPLATE =  new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {64, 256}, {32, 32});
    RESOURCE_TOP_GRAIN_LEATHER_PANTS =        new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {64, 288}, {32, 32});
    RESOURCE_TOP_GRAIN_LEATHER_BOOTS =        new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {64, 320}, {32, 32});
    RESOURCE_RUSTY_HELMET =                   new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {96, 256}, {32, 32});
    RESOURCE_RUSTY_BREASTPLATE =              new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {96, 256}, {32, 32});
    RESOURCE_RUSTY_PANTS =                    new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {96, 288}, {32, 32});
    RESOURCE_RUSTY_BOOTS =                    new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {96, 320}, {32, 32});
    RESOURCE_CHAINMAIL_HELMET =               new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {128, 256}, {32, 32});
    RESOURCE_CHAINMAIL_BREASTPLATE =          new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {128, 256}, {32, 32});
    RESOURCE_CHAINMAIL_PANTS =                new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {128, 288}, {32, 32});
    RESOURCE_CHAINMAIL_BOOTS =                new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {128, 320}, {32, 32});
    RESOURCE_IRON_HELMET =                    new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {256, 256}, {32, 32});
    RESOURCE_IRON_BREASTPLATE =               new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {256, 256}, {32, 32});
    RESOURCE_IRON_PANTS =                     new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {256, 288}, {32, 32});
    RESOURCE_IRON_BOOTS =                     new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {256, 320}, {32, 32});
    RESOURCE_GOLD_HELMET =                    new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {448, 256}, {32, 32});
    RESOURCE_GOLD_BREASTPLATE =               new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {448, 256}, {32, 32});
    RESOURCE_GOLD_PANTS =                     new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {448, 288}, {32, 32});
    RESOURCE_GOLD_BOOTS =                     new Sprite(*TEXTURE_ARMOR_WEAPON, sf::Vector2f(1.5f, 1.5f), {448, 320}, {32, 32});

    HITCIRCLE1 = new Sprite(*TEXTURE_CIRCLE1, sf::Vector2f(1.5f, 1.5f), { 0, 0 }, { 275, 275 });
	HITCIRCLE2 = new Sprite(*TEXTURE_CIRCLE2, sf::Vector2f(1.5f, 1.5f), { 0, 0 }, { 275, 275 });
	MAINCIRCLE = new Sprite(*TEXTURE_MAINCIRCLE, sf::Vector2f(1.6f, 1.6f), { 0, 0 }, { 275, 275 });
	BARRE = new Sprite(*TEXTURE_BARRE, sf::Vector2f(1.5f, 1.5f), { 0, 0 }, { 1000, 20 });

    RESOURCE_BUILDING_BLUE = new Sprite(*BUILDING_BLUE, sf::Vector2f(1.5f, 1.5f), { 0, 0 }, { 80, 80 });
	RESOURCE_BUILDING_BLUE2 = new Sprite(*BUILDING_BLUE2, sf::Vector2f(1.5f, 1.5f), { 0, 0 }, { 112, 112 });
	RESOURCE_BUILDING_GREEN = new Sprite(*BUILDING_GREEN, sf::Vector2f(1.5f, 1.5f), { 0, 0 }, { 80, 80 });
	RESOURCE_BUILDING_GREEN2 = new Sprite(*BUILDING_GREEN2, sf::Vector2f(1.5f, 1.5f), { 0, 0 }, { 112, 112 });
	RESOURCE_BUILDING_SHOP = new Sprite(*BUILDING_SHOP, sf::Vector2f(1.5f, 1.5f), { 0, 0 }, { 80, 80 });
	RESOURCE_BUILDING_MEDIC = new Sprite(*BUILDING_MEDIC, sf::Vector2f(1.5f, 1.5f), { 0, 0 }, { 96, 95 });

    RESOURCE_BACKGROUND = new Sprite(*TEXTURE_BACKGROUND, sf::Vector2f(1.5f, 1.5f), { 0, 0 }, { 1920, 1080 });

    WORKSTATION = new Sprite(*TEXTURE_WORKBENCH, sf::Vector2f(3.f, 3.f), {100, 64}, {100, 50});
    ITEMBOX = new Sprite(*TEXTURE_ITEMBOX);
	
    FURNACE = new SpriteSheet(*TEXTURE_FURNACE);
	FURNACE->Extract(0, 0, 48, 64, 96, 128);
	
    ANVIL = new SpriteSheet(*TEXTURE_ANVIL);
	ANVIL->Extract(0, 0, 64, 80, 512, 320, true);
	
    PLAYER_IDLE = new SpriteSheet(*IDLE_PLAYER_TEXTURE);
    PLAYER_IDLE->Extract(0, 0, 80, 48, 80, 48);

    PLAYER_WALK = new SpriteSheet(*WALK_PLAYER_TEXTURE);
    PLAYER_WALK->Extract(0, 0, 80, 48, 640, 48);

    EVIL_EYE_IDLE = new SpriteSheet(*IDLE_EVIL_EYE_TEXTURE);
    EVIL_EYE_IDLE->Extract(0, 0, 60, 57, 1200, 57);

    EVIL_EYE_ATTACK = new SpriteSheet(*ATTACK_EVIL_EYE_TEXTURE);
    EVIL_EYE_ATTACK->Extract(0, 0, 60, 57, 1020, 57);

    FROST_GUARDIAN_IDLE = new SpriteSheet(*IDLE_FROST_GUARDIAN_TEXTURE);
    FROST_GUARDIAN_IDLE->Extract(0, 0, 192, 128, 1152, 128);

    FROST_GUARDIAN_ATTACK = new SpriteSheet(*ATTACK_FROST_GUARDIAN_TEXTURE);
    FROST_GUARDIAN_ATTACK->Extract(0, 0, 192, 128, 2688, 128);

    GROLUX_IDLE = new SpriteSheet(*IDLE_GROLUX_TEXTURE);
    GROLUX_IDLE->Extract(0, 0, 128, 128, 640, 128);

    GROLUX_ATTACK = new SpriteSheet(*ATTACK_GROLUX_TEXTURE);
    GROLUX_ATTACK->Extract(0, 0, 384, 128, 7296, 128);

}

void Resources::CreateFonts()
{
    DEFAULT_FONT = new sf::Font("../../res/Fonts/font.otf");
}
