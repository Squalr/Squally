#include "SilverRingRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SilverRingRecipe::SaveKey = "silver-ring-recipe";

SilverRingRecipe* SilverRingRecipe::create()
{
	SilverRingRecipe* instance = new SilverRingRecipe();

	instance->autorelease();

	return instance;
}

SilverRingRecipe::SilverRingRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SilverRingRecipe::~SilverRingRecipe()
{
}

std::vector<Item*> SilverRingRecipe::craft()
{
	return { SilverRing::create() };
}

std::vector<std::tuple<Item*, int>> SilverRingRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* SilverRingRecipe::clone()
{
	return SilverRingRecipe::create();
}

LocalizedString* SilverRingRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_SilverRing::create();
}

const std::string& SilverRingRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SilverRingRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings_SilverRing;
}

const std::string& SilverRingRecipe::getIdentifier()
{
	return SilverRingRecipe::SaveKey;
}
