#include "AquaMarineEarringsRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AquaMarineEarringsRecipe::SaveKey = "aquamarine-earrings-recipe";

AquaMarineEarringsRecipe* AquaMarineEarringsRecipe::create()
{
	AquaMarineEarringsRecipe* instance = new AquaMarineEarringsRecipe();

	instance->autorelease();

	return instance;
}

AquaMarineEarringsRecipe::AquaMarineEarringsRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

AquaMarineEarringsRecipe::~AquaMarineEarringsRecipe()
{
}

std::vector<Item*> AquaMarineEarringsRecipe::craft()
{
	return { AquaMarineEarrings::create() };
}

std::vector<std::tuple<Item*, int>> AquaMarineEarringsRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* AquaMarineEarringsRecipe::clone()
{
	return AquaMarineEarringsRecipe::create();
}

LocalizedString* AquaMarineEarringsRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_AquaMarineEarrings::create();
}

const std::string& AquaMarineEarringsRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string AquaMarineEarringsRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_AquaMarineEarrings;
}

const std::string& AquaMarineEarringsRecipe::getIdentifier()
{
	return AquaMarineEarringsRecipe::SaveKey;
}
