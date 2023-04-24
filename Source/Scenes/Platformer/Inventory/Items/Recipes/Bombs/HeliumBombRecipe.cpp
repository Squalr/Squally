#include "HeliumBombRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HeliumBombRecipe::SaveKey = "big-bomb-recipe";

HeliumBombRecipe* HeliumBombRecipe::create()
{
	HeliumBombRecipe* instance = new HeliumBombRecipe();

	instance->autorelease();

	return instance;
}

HeliumBombRecipe::HeliumBombRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 100 }}))
{
}

HeliumBombRecipe::~HeliumBombRecipe()
{
}

std::vector<Item*> HeliumBombRecipe::craft()
{
	return { HeliumBomb::create() };
}

std::vector<std::tuple<Item*, int>> HeliumBombRecipe::getReagentsInternal()
{
	return
	{
		{ UnstableConcoction::create(), 1 },
		{ UnstableElement::create(), 1 },
	};
}

Item* HeliumBombRecipe::clone()
{
	return HeliumBombRecipe::create();
}

LocalizedString* HeliumBombRecipe::getString()
{
	return Strings::Items_Misc_Keys_HeliumBomb::create();
}

const std::string& HeliumBombRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string HeliumBombRecipe::getCraftedItemIconResource()
{
	return ItemResources::Keys_HeliumBomb;
}

const std::string& HeliumBombRecipe::getIdentifier()
{
	return HeliumBombRecipe::SaveKey;
}
