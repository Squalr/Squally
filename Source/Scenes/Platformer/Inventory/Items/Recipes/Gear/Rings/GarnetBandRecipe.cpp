#include "GarnetBandRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GarnetBandRecipe::SaveKey = "garnet-band-recipe";

GarnetBandRecipe* GarnetBandRecipe::create()
{
	GarnetBandRecipe* instance = new GarnetBandRecipe();

	instance->autorelease();

	return instance;
}

GarnetBandRecipe::GarnetBandRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GarnetBandRecipe::~GarnetBandRecipe()
{
}

std::vector<Item*> GarnetBandRecipe::craft()
{
	return { GarnetBand::create() };
}

std::vector<std::tuple<Item*, int>> GarnetBandRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* GarnetBandRecipe::clone()
{
	return GarnetBandRecipe::create();
}

LocalizedString* GarnetBandRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_GarnetBand::create();
}

const std::string& GarnetBandRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GarnetBandRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings_GarnetBand;
}

const std::string& GarnetBandRecipe::getIdentifier()
{
	return GarnetBandRecipe::SaveKey;
}
