#include "GoldenRingRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenRingRecipe::SaveKey = "golden-ring-recipe";

GoldenRingRecipe* GoldenRingRecipe::create()
{
	GoldenRingRecipe* instance = new GoldenRingRecipe();

	instance->autorelease();

	return instance;
}

GoldenRingRecipe::GoldenRingRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GoldenRingRecipe::~GoldenRingRecipe()
{
}

std::vector<Item*> GoldenRingRecipe::craft()
{
	return { GoldenRing::create() };
}

std::vector<std::tuple<Item*, int>> GoldenRingRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* GoldenRingRecipe::clone()
{
	return GoldenRingRecipe::create();
}

LocalizedString* GoldenRingRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_GoldenRing::create();
}

const std::string& GoldenRingRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GoldenRingRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings__Deprecated_T2_GoldenRing;
}

const std::string& GoldenRingRecipe::getIdentifier()
{
	return GoldenRingRecipe::SaveKey;
}
