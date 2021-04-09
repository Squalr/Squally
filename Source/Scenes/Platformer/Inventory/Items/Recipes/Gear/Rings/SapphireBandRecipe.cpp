#include "SapphireBandRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SapphireBandRecipe::SaveKey = "sapphire-band-recipe";

SapphireBandRecipe* SapphireBandRecipe::create()
{
	SapphireBandRecipe* instance = new SapphireBandRecipe();

	instance->autorelease();

	return instance;
}

SapphireBandRecipe::SapphireBandRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SapphireBandRecipe::~SapphireBandRecipe()
{
}

std::vector<Item*> SapphireBandRecipe::craft()
{
	return { SapphireBand::create() };
}

std::vector<std::tuple<Item*, int>> SapphireBandRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* SapphireBandRecipe::clone()
{
	return SapphireBandRecipe::create();
}

LocalizedString* SapphireBandRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_SapphireBand::create();
}

const std::string& SapphireBandRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SapphireBandRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings_SapphireBand;
}

const std::string& SapphireBandRecipe::getIdentifier()
{
	return SapphireBandRecipe::SaveKey;
}
