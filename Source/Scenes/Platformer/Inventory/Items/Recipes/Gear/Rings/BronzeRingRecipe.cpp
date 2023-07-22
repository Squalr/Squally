#include "BronzeRingRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BronzeRingRecipe::SaveKey = "bronze-ring-recipe";

BronzeRingRecipe* BronzeRingRecipe::create()
{
	BronzeRingRecipe* instance = new BronzeRingRecipe();

	instance->autorelease();

	return instance;
}

BronzeRingRecipe::BronzeRingRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BronzeRingRecipe::~BronzeRingRecipe()
{
}

std::vector<Item*> BronzeRingRecipe::craft()
{
	return { BronzeRing::create() };
}

std::vector<std::tuple<Item*, int>> BronzeRingRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* BronzeRingRecipe::clone()
{
	return BronzeRingRecipe::create();
}

LocalizedString* BronzeRingRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_BronzeRing::create();
}

const std::string& BronzeRingRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string BronzeRingRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings__Deprecated_T0_BronzeRing;
}

const std::string& BronzeRingRecipe::getIdentifier()
{
	return BronzeRingRecipe::SaveKey;
}
