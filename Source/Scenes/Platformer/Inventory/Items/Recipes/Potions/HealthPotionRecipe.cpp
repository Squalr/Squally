#include "HealthPotionRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HealthPotionRecipe::SaveKey = "health-potion-recipe";

HealthPotionRecipe* HealthPotionRecipe::create()
{
	HealthPotionRecipe* instance = new HealthPotionRecipe();

	instance->autorelease();

	return instance;
}

HealthPotionRecipe::HealthPotionRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}))
{
}

HealthPotionRecipe::~HealthPotionRecipe()
{
}

Item* HealthPotionRecipe::craft()
{
	return HealthPotion::create();
}

std::vector<std::tuple<Item*, int>> HealthPotionRecipe::getReagentsInternal()
{
	return
	{
		{ DarkSeed::create(), 3 },
		{ Honey::create(), 2 },
	};
}

Item* HealthPotionRecipe::clone()
{
	return HealthPotionRecipe::create();
}

std::string HealthPotionRecipe::getItemName()
{
	return HealthPotionRecipe::SaveKey;
}

LocalizedString* HealthPotionRecipe::getString()
{
	return Strings::Items_Consumables_Health_HealthPotion::create();
}

std::string HealthPotionRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string HealthPotionRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Potions_HealthPotion;
}

std::string HealthPotionRecipe::getSerializationKey()
{
	return HealthPotionRecipe::SaveKey;
}
