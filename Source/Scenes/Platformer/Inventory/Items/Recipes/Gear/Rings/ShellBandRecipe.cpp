#include "ShellBandRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ShellBandRecipe::SaveKey = "shell-band-recipe";

ShellBandRecipe* ShellBandRecipe::create()
{
	ShellBandRecipe* instance = new ShellBandRecipe();

	instance->autorelease();

	return instance;
}

ShellBandRecipe::ShellBandRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

ShellBandRecipe::~ShellBandRecipe()
{
}

std::vector<Item*> ShellBandRecipe::craft()
{
	return { ShellBand::create() };
}

std::vector<std::tuple<Item*, int>> ShellBandRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* ShellBandRecipe::clone()
{
	return ShellBandRecipe::create();
}

LocalizedString* ShellBandRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Rings_ShellBand::create();
}

const std::string& ShellBandRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string ShellBandRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Rings_ShellBand;
}

const std::string& ShellBandRecipe::getIdentifier()
{
	return ShellBandRecipe::SaveKey;
}
