#include "IncrementHealthFlaskRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IncrementHealthFlaskRecipe::SaveKey = "increment-health-flask-recipe";

IncrementHealthFlaskRecipe* IncrementHealthFlaskRecipe::create()
{
	IncrementHealthFlaskRecipe* instance = new IncrementHealthFlaskRecipe();

	instance->autorelease();

	return instance;
}

IncrementHealthFlaskRecipe::IncrementHealthFlaskRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

IncrementHealthFlaskRecipe::~IncrementHealthFlaskRecipe()
{
}

std::vector<Item*> IncrementHealthFlaskRecipe::craft()
{
	return { IncrementHealthFlask::create() };
}

std::vector<std::tuple<Item*, int>> IncrementHealthFlaskRecipe::getReagentsInternal()
{
	return
	{
		{ Clover::create(), 1 },
		{ DarkSeed::create(), 1 },
		{ Honey::create(), 1 },
	};
}

Item* IncrementHealthFlaskRecipe::clone()
{
	return IncrementHealthFlaskRecipe::create();
}

const std::string& IncrementHealthFlaskRecipe::getItemName()
{
	return IncrementHealthFlaskRecipe::SaveKey;
}

LocalizedString* IncrementHealthFlaskRecipe::getString()
{
	return Strings::Items_Consumables_Health_IncrementHealthFlask::create();
}

const std::string& IncrementHealthFlaskRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string IncrementHealthFlaskRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Potions_HealthFlaskIncrement;
}

const std::string& IncrementHealthFlaskRecipe::getIdentifier()
{
	return IncrementHealthFlaskRecipe::SaveKey;
}
