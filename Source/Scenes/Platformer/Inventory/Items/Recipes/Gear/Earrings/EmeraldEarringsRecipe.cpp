#include "EmeraldEarringsRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EmeraldEarringsRecipe::SaveKey = "emerald-earrings-recipe";

EmeraldEarringsRecipe* EmeraldEarringsRecipe::create()
{
	EmeraldEarringsRecipe* instance = new EmeraldEarringsRecipe();

	instance->autorelease();

	return instance;
}

EmeraldEarringsRecipe::EmeraldEarringsRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

EmeraldEarringsRecipe::~EmeraldEarringsRecipe()
{
}

std::vector<Item*> EmeraldEarringsRecipe::craft()
{
	return { EmeraldEarrings::create() };
}

std::vector<std::tuple<Item*, int>> EmeraldEarringsRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* EmeraldEarringsRecipe::clone()
{
	return EmeraldEarringsRecipe::create();
}

LocalizedString* EmeraldEarringsRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_EmeraldEarrings::create();
}

const std::string& EmeraldEarringsRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string EmeraldEarringsRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_EmeraldEarrings;
}

const std::string& EmeraldEarringsRecipe::getIdentifier()
{
	return EmeraldEarringsRecipe::SaveKey;
}
