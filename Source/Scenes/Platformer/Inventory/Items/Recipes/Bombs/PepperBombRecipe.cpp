#include "PepperBombRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PepperBombRecipe::SaveKey = "pepper-bomb-recipe";

PepperBombRecipe* PepperBombRecipe::create()
{
	PepperBombRecipe* instance = new PepperBombRecipe();

	instance->autorelease();

	return instance;
}

PepperBombRecipe::PepperBombRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 44 }}))
{
}

PepperBombRecipe::~PepperBombRecipe()
{
}

std::vector<Item*> PepperBombRecipe::craft()
{
	return { PepperBomb::create() };
}

std::vector<std::tuple<Item*, int>> PepperBombRecipe::getReagentsInternal()
{
	return
	{
		{ Mithril::create(), 2 },
		{ GunpowderT4::create(), 1 },
		{ Pepper::create(), 1 },
		{ Coal::create(), 2 },
	};
}

Item* PepperBombRecipe::clone()
{
	return PepperBombRecipe::create();
}

LocalizedString* PepperBombRecipe::getString()
{
	return Strings::Items_Consumables_Combat_PepperBomb::create();
}

const std::string& PepperBombRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string PepperBombRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Combat_T4_PepperBomb;
}

const std::string& PepperBombRecipe::getIdentifier()
{
	return PepperBombRecipe::SaveKey;
}
