#include "AquaMarineNecklaceRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AquaMarineNecklaceRecipe::SaveKey = "aquamarine-necklace-recipe";

AquaMarineNecklaceRecipe* AquaMarineNecklaceRecipe::create()
{
	AquaMarineNecklaceRecipe* instance = new AquaMarineNecklaceRecipe();

	instance->autorelease();

	return instance;
}

AquaMarineNecklaceRecipe::AquaMarineNecklaceRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

AquaMarineNecklaceRecipe::~AquaMarineNecklaceRecipe()
{
}

std::vector<Item*> AquaMarineNecklaceRecipe::craft()
{
	return { AquaMarineNecklace::create() };
}

std::vector<std::tuple<Item*, int>> AquaMarineNecklaceRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* AquaMarineNecklaceRecipe::clone()
{
	return AquaMarineNecklaceRecipe::create();
}

LocalizedString* AquaMarineNecklaceRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_AquaMarineNecklace::create();
}

const std::string& AquaMarineNecklaceRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string AquaMarineNecklaceRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_AquaMarineNecklace;
}

const std::string& AquaMarineNecklaceRecipe::getIdentifier()
{
	return AquaMarineNecklaceRecipe::SaveKey;
}
