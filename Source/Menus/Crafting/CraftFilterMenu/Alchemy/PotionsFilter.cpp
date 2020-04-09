#include "PotionsFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/PotionRecipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

PotionsFilter* PotionsFilter::create()
{
	PotionsFilter* itemPreview = new PotionsFilter();

	itemPreview->autorelease();

	return itemPreview;
}

PotionsFilter::PotionsFilter() : super (Strings::Menus_Crafting_Potions::create(), UIResources::Menus_CraftingMenu_PotionIcon)
{
}

PotionsFilter::~PotionsFilter()
{
}

void PotionsFilter::onEnter()
{
	super::onEnter();
}

void PotionsFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> PotionsFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<PotionRecipe*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
