#include "GreaterManaPotionRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GreaterManaPotionRecipe::SaveKey = "greater-mana-potion-recipe";

GreaterManaPotionRecipe* GreaterManaPotionRecipe::create()
{
	GreaterManaPotionRecipe* instance = new GreaterManaPotionRecipe();

	instance->autorelease();

	return instance;
}

GreaterManaPotionRecipe::GreaterManaPotionRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 19 }}))
{
}

GreaterManaPotionRecipe::~GreaterManaPotionRecipe()
{
}

std::vector<Item*> GreaterManaPotionRecipe::craft()
{
	return { GreaterManaPotion::create() };
}

std::vector<std::tuple<Item*, int>> GreaterManaPotionRecipe::getReagentsInternal()
{
	return
	{
		{ GoldWeed::create(), 2 },
		{ RatTail::create(), 2 },
	};
}

Item* GreaterManaPotionRecipe::clone()
{
	return GreaterManaPotionRecipe::create();
}

LocalizedString* GreaterManaPotionRecipe::getString()
{
	return Strings::Items_Consumables_Mana_GreaterManaPotion::create();
}

const std::string& GreaterManaPotionRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GreaterManaPotionRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Potions_ManaPotionGreater;
}

const std::string& GreaterManaPotionRecipe::getIdentifier()
{
	return GreaterManaPotionRecipe::SaveKey;
}
