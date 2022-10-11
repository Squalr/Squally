#include "DarkHeartBandRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DarkHeartBandRecipe::SaveKey = "dark-heart-band-recipe";

DarkHeartBandRecipe* DarkHeartBandRecipe::create()
{
	DarkHeartBandRecipe* instance = new DarkHeartBandRecipe();

	instance->autorelease();

	return instance;
}

DarkHeartBandRecipe::DarkHeartBandRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DarkHeartBandRecipe::~DarkHeartBandRecipe()
{
}

std::vector<Item*> DarkHeartBandRecipe::craft()
{
	return { DarkHeartBand::create() };
}

std::vector<std::tuple<Item*, int>> DarkHeartBandRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* DarkHeartBandRecipe::clone()
{
	return DarkHeartBandRecipe::create();
}

LocalizedString* DarkHeartBandRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_DarkHeartBand::create();
}

const std::string& DarkHeartBandRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DarkHeartBandRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings_DarkHeartBand;
}

const std::string& DarkHeartBandRecipe::getIdentifier()
{
	return DarkHeartBandRecipe::SaveKey;
}
