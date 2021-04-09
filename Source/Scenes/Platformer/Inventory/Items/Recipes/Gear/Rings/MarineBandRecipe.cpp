#include "MarineBandRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MarineBandRecipe::SaveKey = "marine-band-recipe";

MarineBandRecipe* MarineBandRecipe::create()
{
	MarineBandRecipe* instance = new MarineBandRecipe();

	instance->autorelease();

	return instance;
}

MarineBandRecipe::MarineBandRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

MarineBandRecipe::~MarineBandRecipe()
{
}

std::vector<Item*> MarineBandRecipe::craft()
{
	return { MarineBand::create() };
}

std::vector<std::tuple<Item*, int>> MarineBandRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* MarineBandRecipe::clone()
{
	return MarineBandRecipe::create();
}

LocalizedString* MarineBandRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_MarineBand::create();
}

const std::string& MarineBandRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MarineBandRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings_MarineBand;
}

const std::string& MarineBandRecipe::getIdentifier()
{
	return MarineBandRecipe::SaveKey;
}
