#include "GreaterHealthPotionRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GreaterHealthPotionRecipe::SaveKey = "greater-health-potion-recipe";

GreaterHealthPotionRecipe* GreaterHealthPotionRecipe::create()
{
	GreaterHealthPotionRecipe* instance = new GreaterHealthPotionRecipe();

	instance->autorelease();

	return instance;
}

GreaterHealthPotionRecipe::GreaterHealthPotionRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}))
{
}

GreaterHealthPotionRecipe::~GreaterHealthPotionRecipe()
{
}

std::vector<Item*> GreaterHealthPotionRecipe::craft()
{
	return { GreaterHealthPotion::create() };
}

std::vector<std::tuple<Item*, int>> GreaterHealthPotionRecipe::getReagentsInternal()
{
	return
	{
		{ DarkSeed::create(), 2 },
		{ SandRoot::create(), 3 },
	};
}

Item* GreaterHealthPotionRecipe::clone()
{
	return GreaterHealthPotionRecipe::create();
}

LocalizedString* GreaterHealthPotionRecipe::getString()
{
	return Strings::Items_Consumables_Health_GreaterHealthPotion::create();
}

const std::string& GreaterHealthPotionRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GreaterHealthPotionRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Potions_HealthPotionGreater;
}

const std::string& GreaterHealthPotionRecipe::getIdentifier()
{
	return GreaterHealthPotionRecipe::SaveKey;
}
