#include "SpikedBombRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpikedBombRecipe::SaveKey = "spiked-bomb-recipe";

SpikedBombRecipe* SpikedBombRecipe::create()
{
	SpikedBombRecipe* instance = new SpikedBombRecipe();

	instance->autorelease();

	return instance;
}

SpikedBombRecipe::SpikedBombRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 55 }}))
{
}

SpikedBombRecipe::~SpikedBombRecipe()
{
}

std::vector<Item*> SpikedBombRecipe::craft()
{
	return { SpikedBomb::create() };
}

std::vector<std::tuple<Item*, int>> SpikedBombRecipe::getReagentsInternal()
{
	return
	{
		{ Bone::create(), 2 },
		{ Stinger::create(), 2 },
		{ Coal::create(), 4 },
	};
}

Item* SpikedBombRecipe::clone()
{
	return SpikedBombRecipe::create();
}

LocalizedString* SpikedBombRecipe::getString()
{
	return Strings::Items_Consumables_Combat_SpikedBomb::create();
}

const std::string& SpikedBombRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SpikedBombRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Combat_T5_SpikedBomb;
}

const std::string& SpikedBombRecipe::getIdentifier()
{
	return SpikedBombRecipe::SaveKey;
}
