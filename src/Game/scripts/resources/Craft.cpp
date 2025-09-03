#include "pch.h"
#include "Craft.h"

#include <utility>

#include "ObjectFactory.h"
#include "ECS/Components/ui/Button.h"
#include "ECS/Components/ui/Image.h"
#include "ECS/Components/ui/ProgressBar.h"
#include "ECS/Components/ui/Text.h"
#include "Utils/Maths.h"

int Recipe::NextId = 0;

Item Result::GetFinalItem()
{

    Item result = item;
    result.actualCount = Maths::RandomInt(MinAmount, MaxAmount);
    if (malus.size() > 0 || bonuses.size() > 0)
    {
        for (MalusType appliedMalus : malus)
        {
            result.malus.emplace(appliedMalus, Maths::RandomFloat(1.0f, 2.0f));
        }
        for (BonusType appliedBonus : bonuses)
        {
            result.bonuses.emplace(appliedBonus, Maths::RandomFloat(1.0f, 2.0f));
        }
    }

    return result;
    
}

void Craft::UpdateText()
{
    for (auto& craftText : mTexts)
    {
        for (auto craftRecipe : craftText.second)
        {
            Item item = mInventory->Items[craftRecipe.first.first];
            std::string info = item.name + " " + std::to_string(item.actualCount) + "/" + std::to_string(craftRecipe.first.second);
            craftRecipe.second->WriteText->setString(info);
        }
    }
}

Craft::Craft(Inventory* inventory, BGMMusicScript* bgm, MusicScript* music, const char* name): mCraftStation(nullptr),
                                                                          mCraftStarted(false),
                                                                          mCraftIndex(0)
{
    mInventory = inventory;
    mMusic = music;
    nameDisplay = std::string(name);
	mBGM = bgm;
}

Craft::~Craft()
{
    mRecipes.clear();
}

void Craft::OnStart()
{

    float baseX = 700;
    float baseY = 500;

    mCraftStation = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Image>(mCraftStation,
                   Resources::instance().INVENTORY, sf::Vector2f(baseX, baseY), sf::Vector2f(5.0f, 5.0f));

    Entity* title = ObjectFactory::CreateEntity<Entity>(mCraftStation);
    ObjectFactory::CreateComponent<Image>(title,
               Resources::instance().UI_TITLE_CONTAINER, sf::Vector2f(baseX + 175.0f, baseY - 30.0f), sf::Vector2f(4.0f, 4.0f));
    ObjectFactory::CreateComponent<Text>(title,
    Resources::instance().DEFAULT_FONT, 20, nameDisplay, sf::Vector2f(baseX + 230.0f, baseY - 15.0f));

    for (int i = 0; i < mRecipes.size(); i++)
    {

        int decalX = i/4 * 140;
        int decalY = i%4 * 140;
        
        Entity* craftSection = ObjectFactory::CreateEntity<Entity>(mCraftStation);
        Recipe* recipe = mRecipes[i];
        mProgressBar.push_back(ObjectFactory::CreateComponent<ProgressBar>(craftSection,
            Resources::instance().BACKGROUND_HEALTH_BAR, Resources::instance().HEALTH_BAR,
            sf::Vector2f(baseX + 55.0f + decalX, baseY + 152.0f + decalY), sf::Vector2f(4.0f, 4.0f)));
        mProgressBar[i]->Maximum = 7.0f;

        int recipeIndex = 0;
        for (auto& needForCraft : recipe->cost)
        {
            Entity* need = ObjectFactory::CreateEntity<Entity>(craftSection);
            Item item = mInventory->Items[needForCraft.first];
            ObjectFactory::CreateComponent<Image>(need, item.sprite, sf::Vector2f(baseX + 60.0f + decalX, baseY + 65.0f + 20.0f * recipeIndex + decalY));

            if (mTexts.contains(recipe->Id))
            {
                mTexts.at(recipe->Id).emplace( needForCraft,
                    ObjectFactory::CreateComponent<Text>(need, Resources::instance().DEFAULT_FONT,
                        13*zoom, "", sf::Vector2f(baseX + 85.0f + decalX, baseY + 65.0f + 20.0f * recipeIndex + decalY))
                );
            } else
            {
                std::map<std::pair<Material, int>, Text*> texts;
                texts.emplace(needForCraft,
                    ObjectFactory::CreateComponent<Text>(need, Resources::instance().DEFAULT_FONT,
                        13*zoom, "", sf::Vector2f(baseX + 85.0f + decalX, baseY + 65.0f + 20.0f * recipeIndex + decalY)));
                
                mTexts.emplace(recipe->Id, texts);
            }
            
            recipeIndex++;
        }
        recipeIndex = 0;
        unsigned int lastId = -1;
        for (auto recipeOut : recipe->items)
        {
            if (lastId == recipeOut.second.item.id)
                break;
            lastId = recipeOut.second.item.id;
            Entity* crafted = ObjectFactory::CreateEntity<Entity>(craftSection);
            ObjectFactory::CreateComponent<Image>(crafted,
                recipeOut.second.item.sprite, sf::Vector2f(baseX + 60.0f + 30.0f*(recipeIndex++) + decalX, baseY + 134.0f + decalY));
        }
        
        ObjectFactory::CreateComponent<Text>(craftSection,
            Resources::instance().DEFAULT_FONT, 13, recipe->name, sf::Vector2f(baseX + 60.0f + decalX, baseY + 45.0f + decalY));

        const int index = i;
        ObjectFactory::CreateComponent<Button>(craftSection, Resources::instance().INVENTORY,
           sf::Vector2f(baseX + 55.0f + decalX, baseY + 40.0f + decalY), 125.0f*zoom, 125.0f*zoom, [this, i, recipe] {
               for (auto& needed : recipe->cost)
               {
                   if (!mInventory->HasEnough(needed.first, needed.second))
                       return;
               }
               ProgressBar* bar = mProgressBar[i];
               bar->Progress += Engine::GetDeltaTime() * 10.0f;
               if (bar->Progress >= bar->Maximum)
               {
                   mInventory->CloseInventory();
                   mCraftStation->SetEnabled(false);
				   mBGM->PauseBGMMusic(true);
                   mMusic->PlayBeatmap(recipe->musicId);
                   bar->Progress = 0.0f;
                   mCraftStarted = true;
                   mCraftIndex = i;
               }
           }, [this, index] {
               mProgressBar[index]->Progress = 0;
           });
    }
    mCraftStation->SetEnabled(false);
}

void Craft::OnUpdate()
{
    if (mCraftStarted && mMusic->GetState() == MusicScript::MUSICSTATE::STOPPED)
    {
        mBGM->PauseBGMMusic(false);

        MusicScript::PlayerData data = mMusic->GetData();
        Recipe* recipe = mRecipes[mCraftIndex];
        Item lastItem = Item();
        for (auto& needed : recipe->cost)
        {
            mInventory->RemoveItemCount(needed.first, needed.second);
        }
        for (auto& recipeOut : recipe->items)
        {
            if (data.Accuracy/100.0f >= recipeOut.first)
            {
                lastItem = recipeOut.second.GetFinalItem();
            }
        }
        if (lastItem.type == ITEM)
            mInventory->AddItemCount(lastItem.id, lastItem.actualCount);
        else
        {
            mInventory->AddItem(lastItem);
        }
        UpdateText();
        mCraftStation->SetEnabled(true);
        mCraftStarted = false;
    }
}

void Craft::AddCraft(std::string name, int musicId, std::map<Material, int> cost, std::map<float, Result> items)
{
    mRecipes.push_back(new Recipe{name, musicId, cost, items, Recipe::NextId++});
}

void Craft::OnRender(RenderWindow* window)
{
}

void Craft::ToggleState()
{
    UpdateText();
    mCraftStation->SetEnabled(!mCraftStation->IsEnable());
    if (mCraftStation->IsEnable())
        mInventory->DisplayInventory();
    else
        mInventory->CloseInventory();
}

void Craft::Close()
{
    mCraftStation->SetEnabled(false);
}
