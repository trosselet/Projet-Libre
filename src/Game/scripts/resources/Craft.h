#pragma once
#include "ECS/Components/ui/ProgressBar.h"
#include "scripts/Inventory.h"
#include "scripts/MusicScript.h"
#include "scripts/Script.h"
#include "scripts/BGMMusicScript.h"

class Text;
enum class BonusType;
enum class MalusType;

struct Result
{
    Item item;
    int MinAmount, MaxAmount;
    std::vector<MalusType> malus;
    std::vector<BonusType> bonuses;

    Item GetFinalItem();
    
};

struct Recipe
{
    std::string name;
    int musicId;
    std::map<Material, int> cost;
    std::map<float, Result> items;

    int Id;
    static int NextId;
};

class Craft : public IScript
{
    Entity* mCraftStation;
    std::vector<ProgressBar*> mProgressBar;
    std::map<int, std::map<std::pair<Material, int>, Text*>> mTexts;
    std::vector<Recipe*> mRecipes;
    Inventory* mInventory;
    MusicScript* mMusic;
	BGMMusicScript* mBGM;
    std::string nameDisplay;

    bool mCraftStarted;
    int mCraftIndex;

    void UpdateText();

public:
    float zoom = 0.65f;
    Craft(Inventory* inventory, BGMMusicScript* bgm, MusicScript* music, const char* name);
    ~Craft() override;

    void OnStart() override;
    void OnUpdate() override;
    void AddCraft(std::string name, int musicId, std::map<Material, int> cost = {}, std::map<float, Result> items = {});
    void OnRender(RenderWindow* window) override;

    void ToggleState() ;
    void Close() ;
};
