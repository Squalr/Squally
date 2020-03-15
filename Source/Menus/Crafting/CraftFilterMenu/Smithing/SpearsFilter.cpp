#include "SpearsFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Spears/SpearRecipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

SpearsFilter* SpearsFilter::create()
{
	SpearsFilter* itemPreview = new SpearsFilter();

	itemPreview->autorelease();

	return itemPreview;
}

SpearsFilter::SpearsFilter() : super (Strings::Menus_Crafting_Spears::create(), UIResources::Menus_CraftingMenu_SpearIcon)
{
}

SpearsFilter::~SpearsFilter()
{
}

void SpearsFilter::onEnter()
{
	super::onEnter();
}

void SpearsFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> SpearsFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<SpearRecipe*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
