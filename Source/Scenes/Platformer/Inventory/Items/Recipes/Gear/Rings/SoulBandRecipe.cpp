#include "SoulBandRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SoulBandRecipe::SaveKey = "soul-band-recipe";

SoulBandRecipe* SoulBandRecipe::create()
{
	SoulBandRecipe* instance = new SoulBandRecipe();

	instance->autorelease();

	return instance;
}

SoulBandRecipe::SoulBandRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SoulBandRecipe::~SoulBandRecipe()
{
}

std::vector<Item*> SoulBandRecipe::craft()
{
	return { SoulBand::create() };
}

std::vector<std::tuple<Item*, int>> SoulBandRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* SoulBandRecipe::clone()
{
	return SoulBandRecipe::create();
}

LocalizedString* SoulBandRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_SoulBand::create();
}

const std::string& SoulBandRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SoulBandRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings_SoulBand;
}

const std::string& SoulBandRecipe::getIdentifier()
{
	return SoulBandRecipe::SaveKey;
}
