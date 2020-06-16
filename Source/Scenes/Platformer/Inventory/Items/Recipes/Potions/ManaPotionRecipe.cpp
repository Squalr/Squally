#include "ManaPotionRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ManaPotionRecipe::SaveKey = "mana-potion-recipe";

ManaPotionRecipe* ManaPotionRecipe::create()
{
	ManaPotionRecipe* instance = new ManaPotionRecipe();

	instance->autorelease();

	return instance;
}

ManaPotionRecipe::ManaPotionRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 9 }}))
{
}

ManaPotionRecipe::~ManaPotionRecipe()
{
}

Item* ManaPotionRecipe::craft()
{
	return ManaPotion::create();
}

std::vector<std::tuple<Item*, int>> ManaPotionRecipe::getReagentsInternal()
{
	return
	{
		{ Clover::create(), 2 },
		{ Feather::create(), 2 },
	};
}

Item* ManaPotionRecipe::clone()
{
	return ManaPotionRecipe::create();
}

std::string ManaPotionRecipe::getItemName()
{
	return ManaPotionRecipe::SaveKey;
}

LocalizedString* ManaPotionRecipe::getString()
{
	return Strings::Items_Consumables_Mana_ManaPotion::create();
}

std::string ManaPotionRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string ManaPotionRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Potions_ManaPotion;
}

std::string ManaPotionRecipe::getSerializationKey()
{
	return ManaPotionRecipe::SaveKey;
}
