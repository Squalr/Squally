#include "AllAlchemyFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

AllAlchemyFilter* AllAlchemyFilter::create()
{
	AllAlchemyFilter* itemPreview = new AllAlchemyFilter();

	itemPreview->autorelease();

	return itemPreview;
}

AllAlchemyFilter::AllAlchemyFilter() : super (Strings::Menus_Crafting_All::create(), UIResources::Menus_CraftingMenu_AllIcon)
{
}

AllAlchemyFilter::~AllAlchemyFilter()
{
}

void AllAlchemyFilter::onEnter()
{
	super::onEnter();
}

void AllAlchemyFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> AllAlchemyFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<Recipe*>(item) == nullptr; 
	}), itemList.end());

	return itemList;
}
