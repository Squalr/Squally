#include "SkullBandRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkullBandRecipe::SaveKey = "skull-band-recipe";

SkullBandRecipe* SkullBandRecipe::create()
{
	SkullBandRecipe* instance = new SkullBandRecipe();

	instance->autorelease();

	return instance;
}

SkullBandRecipe::SkullBandRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SkullBandRecipe::~SkullBandRecipe()
{
}

std::vector<Item*> SkullBandRecipe::craft()
{
	return { SkullBand::create() };
}

std::vector<std::tuple<Item*, int>> SkullBandRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* SkullBandRecipe::clone()
{
	return SkullBandRecipe::create();
}

LocalizedString* SkullBandRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_SkullBand::create();
}

const std::string& SkullBandRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SkullBandRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings_SkullBand;
}

const std::string& SkullBandRecipe::getIdentifier()
{
	return SkullBandRecipe::SaveKey;
}
