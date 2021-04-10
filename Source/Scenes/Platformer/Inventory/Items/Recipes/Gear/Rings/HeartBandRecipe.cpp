#include "HeartBandRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HeartBandRecipe::SaveKey = "heart-band-recipe";

HeartBandRecipe* HeartBandRecipe::create()
{
	HeartBandRecipe* instance = new HeartBandRecipe();

	instance->autorelease();

	return instance;
}

HeartBandRecipe::HeartBandRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

HeartBandRecipe::~HeartBandRecipe()
{
}

std::vector<Item*> HeartBandRecipe::craft()
{
	return { HeartBand::create() };
}

std::vector<std::tuple<Item*, int>> HeartBandRecipe::getReagentsInternal()
{
	return
	{
		{ Gold::create(), 2 },
		{ Ruby::create(), 2 },
	};
}

Item* HeartBandRecipe::clone()
{
	return HeartBandRecipe::create();
}

LocalizedString* HeartBandRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_HeartBand::create();
}

const std::string& HeartBandRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string HeartBandRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings_HeartBand;
}

const std::string& HeartBandRecipe::getIdentifier()
{
	return HeartBandRecipe::SaveKey;
}
