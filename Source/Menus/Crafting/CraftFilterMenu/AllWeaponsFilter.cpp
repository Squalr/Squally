#include "AllWeaponsFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

AllWeaponsFilter* AllWeaponsFilter::create()
{
	AllWeaponsFilter* itemPreview = new AllWeaponsFilter();

	itemPreview->autorelease();

	return itemPreview;
}

AllWeaponsFilter::AllWeaponsFilter() : super (Strings::Menus_Crafting_All::create(), UIResources::Menus_CraftingMenu_AllIcon)
{
}

AllWeaponsFilter::~AllWeaponsFilter()
{
}

void AllWeaponsFilter::onEnter()
{
	super::onEnter();
}

void AllWeaponsFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> AllWeaponsFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<Recipe*>(item) == nullptr; 
	}), itemList.end());

	return itemList;
}
