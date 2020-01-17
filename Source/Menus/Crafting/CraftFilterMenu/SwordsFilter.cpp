#include "SwordsFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/SwordRecipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

SwordsFilter* SwordsFilter::create()
{
	SwordsFilter* itemPreview = new SwordsFilter();

	itemPreview->autorelease();

	return itemPreview;
}

SwordsFilter::SwordsFilter() : super (Strings::Menus_Crafting_Swords::create(), UIResources::Menus_CraftingMenu_SwordIcon)
{
}

SwordsFilter::~SwordsFilter()
{
}

void SwordsFilter::onEnter()
{
	super::onEnter();
}

void SwordsFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> SwordsFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<SwordRecipe*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
