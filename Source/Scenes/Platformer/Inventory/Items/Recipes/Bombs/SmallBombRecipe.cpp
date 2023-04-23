#include "SmallBombRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SmallBombRecipe::SaveKey = "small-bomb-recipe";

SmallBombRecipe* SmallBombRecipe::create()
{
	SmallBombRecipe* instance = new SmallBombRecipe();

	instance->autorelease();

	return instance;
}

SmallBombRecipe::SmallBombRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 11 }}))
{
}

SmallBombRecipe::~SmallBombRecipe()
{
}

std::vector<Item*> SmallBombRecipe::craft()
{
	return { SmallBomb::create() };
}

std::vector<std::tuple<Item*, int>> SmallBombRecipe::getReagentsInternal()
{
	return
	{
		{ Copper::create(), 1 },
		{ Coal::create(), 2 },
		{ Bamboo::create(), 2 },
	};
}

Item* SmallBombRecipe::clone()
{
	return SmallBombRecipe::create();
}

LocalizedString* SmallBombRecipe::getString()
{
	return Strings::Items_Consumables_Combat_SmallBomb::create();
}

const std::string& SmallBombRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SmallBombRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Combat_T1_SmallBomb;
}

const std::string& SmallBombRecipe::getIdentifier()
{
	return SmallBombRecipe::SaveKey;
}
