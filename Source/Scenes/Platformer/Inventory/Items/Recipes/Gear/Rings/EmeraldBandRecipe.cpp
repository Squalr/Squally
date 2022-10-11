#include "EmeraldBandRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EmeraldBandRecipe::SaveKey = "emerald-band-recipe";

EmeraldBandRecipe* EmeraldBandRecipe::create()
{
	EmeraldBandRecipe* instance = new EmeraldBandRecipe();

	instance->autorelease();

	return instance;
}

EmeraldBandRecipe::EmeraldBandRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

EmeraldBandRecipe::~EmeraldBandRecipe()
{
}

std::vector<Item*> EmeraldBandRecipe::craft()
{
	return { EmeraldBand::create() };
}

std::vector<std::tuple<Item*, int>> EmeraldBandRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* EmeraldBandRecipe::clone()
{
	return EmeraldBandRecipe::create();
}

LocalizedString* EmeraldBandRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_EmeraldBand::create();
}

const std::string& EmeraldBandRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string EmeraldBandRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings_EmeraldBand;
}

const std::string& EmeraldBandRecipe::getIdentifier()
{
	return EmeraldBandRecipe::SaveKey;
}
