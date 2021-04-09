#include "AmethystNecklaceRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AmethystNecklaceRecipe::SaveKey = "amethyst-necklace-recipe";

AmethystNecklaceRecipe* AmethystNecklaceRecipe::create()
{
	AmethystNecklaceRecipe* instance = new AmethystNecklaceRecipe();

	instance->autorelease();

	return instance;
}

AmethystNecklaceRecipe::AmethystNecklaceRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

AmethystNecklaceRecipe::~AmethystNecklaceRecipe()
{
}

std::vector<Item*> AmethystNecklaceRecipe::craft()
{
	return { AmethystNecklace::create() };
}

std::vector<std::tuple<Item*, int>> AmethystNecklaceRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* AmethystNecklaceRecipe::clone()
{
	return AmethystNecklaceRecipe::create();
}

LocalizedString* AmethystNecklaceRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_AmethystNecklace::create();
}

const std::string& AmethystNecklaceRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string AmethystNecklaceRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_AmethystNecklace;
}

const std::string& AmethystNecklaceRecipe::getIdentifier()
{
	return AmethystNecklaceRecipe::SaveKey;
}
