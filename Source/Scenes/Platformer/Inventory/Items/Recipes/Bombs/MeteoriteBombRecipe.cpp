#include "MeteoriteBombRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MeteoriteBombRecipe::SaveKey = "meteorite-bomb-recipe";

MeteoriteBombRecipe* MeteoriteBombRecipe::create()
{
	MeteoriteBombRecipe* instance = new MeteoriteBombRecipe();

	instance->autorelease();

	return instance;
}

MeteoriteBombRecipe::MeteoriteBombRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 77 }}))
{
}

MeteoriteBombRecipe::~MeteoriteBombRecipe()
{
}

std::vector<Item*> MeteoriteBombRecipe::craft()
{
	return { MeteoriteBomb::create() };
}

std::vector<std::tuple<Item*, int>> MeteoriteBombRecipe::getReagentsInternal()
{
	return
	{
		{ Obsidian::create(), 2 },
		{ GunpowderT7::create(), 1 },
		{ Meteorite::create(), 1 },
		{ Coal::create(), 5 },
	};
}

Item* MeteoriteBombRecipe::clone()
{
	return MeteoriteBombRecipe::create();
}

LocalizedString* MeteoriteBombRecipe::getString()
{
	return Strings::Items_Consumables_Combat_MeteoriteBomb::create();
}

const std::string& MeteoriteBombRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MeteoriteBombRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Combat_T7_MeteoriteBomb;
}

const std::string& MeteoriteBombRecipe::getIdentifier()
{
	return MeteoriteBombRecipe::SaveKey;
}
