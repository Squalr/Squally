#include "LargeBombRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LargeBombRecipe::SaveKey = "large-bomb-recipe";

LargeBombRecipe* LargeBombRecipe::create()
{
	LargeBombRecipe* instance = new LargeBombRecipe();

	instance->autorelease();

	return instance;
}

LargeBombRecipe::LargeBombRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 33 }}))
{
}

LargeBombRecipe::~LargeBombRecipe()
{
}

std::vector<Item*> LargeBombRecipe::craft()
{
	return { LargeBomb::create() };
}

std::vector<std::tuple<Item*, int>> LargeBombRecipe::getReagentsInternal()
{
	return
	{
		{ Gold::create(), 2 },
		{ StrongChitin::create(), 2 },
		{ Coal::create(), 2 },
	};
}

Item* LargeBombRecipe::clone()
{
	return LargeBombRecipe::create();
}

LocalizedString* LargeBombRecipe::getString()
{
	return Strings::Items_Consumables_Combat_LargeBomb::create();
}

const std::string& LargeBombRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string LargeBombRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Combat_T3_LargeBomb;
}

const std::string& LargeBombRecipe::getIdentifier()
{
	return LargeBombRecipe::SaveKey;
}
