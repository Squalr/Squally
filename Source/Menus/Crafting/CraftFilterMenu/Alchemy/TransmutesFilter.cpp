#include "TransmutesFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Transmutes/TransmuteRecipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TransmutesFilter* TransmutesFilter::create()
{
	TransmutesFilter* itemPreview = new TransmutesFilter();

	itemPreview->autorelease();

	return itemPreview;
}

TransmutesFilter::TransmutesFilter() : super (Strings::Menus_Crafting_Transmutes::create(), UIResources::Menus_CraftingMenu_TransmuteIcon)
{
}

TransmutesFilter::~TransmutesFilter()
{
}

void TransmutesFilter::onEnter()
{
	super::onEnter();
}

void TransmutesFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> TransmutesFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<TransmuteRecipe*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
