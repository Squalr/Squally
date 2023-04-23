#include "IncrementManaFlaskRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IncrementManaFlaskRecipe::SaveKey = "increment-mana-flask-recipe";

IncrementManaFlaskRecipe* IncrementManaFlaskRecipe::create()
{
	IncrementManaFlaskRecipe* instance = new IncrementManaFlaskRecipe();

	instance->autorelease();

	return instance;
}

IncrementManaFlaskRecipe::IncrementManaFlaskRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

IncrementManaFlaskRecipe::~IncrementManaFlaskRecipe()
{
}

std::vector<Item*> IncrementManaFlaskRecipe::craft()
{
	return { IncrementManaFlask::create() };
}

std::vector<std::tuple<Item*, int>> IncrementManaFlaskRecipe::getReagentsInternal()
{
	return
	{
		{ Acorn::create(), 2 },
		{ Honey::create(), 2 },
	};
}

Item* IncrementManaFlaskRecipe::clone()
{
	return IncrementManaFlaskRecipe::create();
}

LocalizedString* IncrementManaFlaskRecipe::getString()
{
	return Strings::Items_Consumables_Mana_IncrementManaFlask::create();
}

const std::string& IncrementManaFlaskRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string IncrementManaFlaskRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Potions_ManaFlaskIncrement;
}

const std::string& IncrementManaFlaskRecipe::getIdentifier()
{
	return IncrementManaFlaskRecipe::SaveKey;
}
