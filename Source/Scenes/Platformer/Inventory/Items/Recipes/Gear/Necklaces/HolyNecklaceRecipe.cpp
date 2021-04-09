#include "HolyNecklaceRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HolyNecklaceRecipe::SaveKey = "holy-necklace-recipe";

HolyNecklaceRecipe* HolyNecklaceRecipe::create()
{
	HolyNecklaceRecipe* instance = new HolyNecklaceRecipe();

	instance->autorelease();

	return instance;
}

HolyNecklaceRecipe::HolyNecklaceRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

HolyNecklaceRecipe::~HolyNecklaceRecipe()
{
}

std::vector<Item*> HolyNecklaceRecipe::craft()
{
	return { HolyNecklace::create() };
}

std::vector<std::tuple<Item*, int>> HolyNecklaceRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* HolyNecklaceRecipe::clone()
{
	return HolyNecklaceRecipe::create();
}

LocalizedString* HolyNecklaceRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_HolyNecklace::create();
}

const std::string& HolyNecklaceRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string HolyNecklaceRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_HolyNecklace;
}

const std::string& HolyNecklaceRecipe::getIdentifier()
{
	return HolyNecklaceRecipe::SaveKey;
}
