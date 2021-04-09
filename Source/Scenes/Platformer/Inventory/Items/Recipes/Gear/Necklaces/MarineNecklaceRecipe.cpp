#include "MarineNecklaceRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MarineNecklaceRecipe::SaveKey = "amethyst-necklace-recipe";

MarineNecklaceRecipe* MarineNecklaceRecipe::create()
{
	MarineNecklaceRecipe* instance = new MarineNecklaceRecipe();

	instance->autorelease();

	return instance;
}

MarineNecklaceRecipe::MarineNecklaceRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

MarineNecklaceRecipe::~MarineNecklaceRecipe()
{
}

std::vector<Item*> MarineNecklaceRecipe::craft()
{
	return { MarineNecklace::create() };
}

std::vector<std::tuple<Item*, int>> MarineNecklaceRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* MarineNecklaceRecipe::clone()
{
	return MarineNecklaceRecipe::create();
}

LocalizedString* MarineNecklaceRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_MarineNecklace::create();
}

const std::string& MarineNecklaceRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MarineNecklaceRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_MarineNecklace;
}

const std::string& MarineNecklaceRecipe::getIdentifier()
{
	return MarineNecklaceRecipe::SaveKey;
}
