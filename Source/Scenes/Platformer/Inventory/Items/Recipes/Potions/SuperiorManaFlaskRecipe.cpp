#include "SuperiorManaFlaskRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SuperiorManaFlaskRecipe::SaveKey = "superior-mana-flask-recipe";

SuperiorManaFlaskRecipe* SuperiorManaFlaskRecipe::create()
{
	SuperiorManaFlaskRecipe* instance = new SuperiorManaFlaskRecipe();

	instance->autorelease();

	return instance;
}

SuperiorManaFlaskRecipe::SuperiorManaFlaskRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 29 }}))
{
}

SuperiorManaFlaskRecipe::~SuperiorManaFlaskRecipe()
{
}

std::vector<Item*> SuperiorManaFlaskRecipe::craft()
{
	return { ManaPotion::create() };
}

std::vector<std::tuple<Item*, int>> SuperiorManaFlaskRecipe::getReagentsInternal()
{
	return
	{
		{ Clover::create(), 2 },
		{ Feather::create(), 1 },
	};
}

Item* SuperiorManaFlaskRecipe::clone()
{
	return SuperiorManaFlaskRecipe::create();
}

LocalizedString* SuperiorManaFlaskRecipe::getString()
{
	return Strings::Items_Consumables_Mana_SuperiorManaFlask::create();
}

const std::string& SuperiorManaFlaskRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SuperiorManaFlaskRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Potions_ManaFlaskSuperior;
}

const std::string& SuperiorManaFlaskRecipe::getIdentifier()
{
	return SuperiorManaFlaskRecipe::SaveKey;
}
