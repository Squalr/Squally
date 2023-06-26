#include "SteelBombRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelBombRecipe::SaveKey = "steel-bomb-recipe";

SteelBombRecipe* SteelBombRecipe::create()
{
	SteelBombRecipe* instance = new SteelBombRecipe();

	instance->autorelease();

	return instance;
}

SteelBombRecipe::SteelBombRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 22 }}))
{
}

SteelBombRecipe::~SteelBombRecipe()
{
}

std::vector<Item*> SteelBombRecipe::craft()
{
	return { SteelBomb::create() };
}

std::vector<std::tuple<Item*, int>> SteelBombRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 2 },
		{ WeakChitin::create(), 2 },
		{ Coal::create(), 2 },
	};
}

Item* SteelBombRecipe::clone()
{
	return SteelBombRecipe::create();
}

LocalizedString* SteelBombRecipe::getString()
{
	return Strings::Items_Consumables_Combat_SteelBomb::create();
}

const std::string& SteelBombRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SteelBombRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Combat_T2_SteelBomb;
}

const std::string& SteelBombRecipe::getIdentifier()
{
	return SteelBombRecipe::SaveKey;
}
