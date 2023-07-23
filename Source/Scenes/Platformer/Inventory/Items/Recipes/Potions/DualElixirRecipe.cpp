#include "DualElixirRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DualElixirRecipe::SaveKey = "dual-elixir-recipe";

DualElixirRecipe* DualElixirRecipe::create()
{
	DualElixirRecipe* instance = new DualElixirRecipe();

	instance->autorelease();

	return instance;
}

DualElixirRecipe::DualElixirRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 57 }}))
{
}

DualElixirRecipe::~DualElixirRecipe()
{
}

std::vector<Item*> DualElixirRecipe::craft()
{
	return { DualElixir::create() };
}

std::vector<std::tuple<Item*, int>> DualElixirRecipe::getReagentsInternal()
{
	return
	{
		{ FrostBerries::create(), 2 },
		{ Snowball::create(), 2 },
	};
}

Item* DualElixirRecipe::clone()
{
	return DualElixirRecipe::create();
}

LocalizedString* DualElixirRecipe::getString()
{
	return Strings::Items_Consumables_Special_DualElixir::create();
}

const std::string& DualElixirRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DualElixirRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Potions_DualElixir;
}

const std::string& DualElixirRecipe::getIdentifier()
{
	return DualElixirRecipe::SaveKey;
}
