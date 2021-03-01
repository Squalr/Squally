#include "SerpentWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/SerpentWandPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SerpentWand::SaveKey = "serpent-wand";

SerpentWand* SerpentWand::create()
{
	SerpentWand* instance = new SerpentWand();

	instance->autorelease();

	return instance;
}

SerpentWand::SerpentWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 10, 12, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.15f
))
{
}

SerpentWand::~SerpentWand()
{
}

Item* SerpentWand::clone()
{
	return SerpentWand::create();
}

std::string SerpentWand::getItemName()
{
	return SerpentWand::SaveKey;
}

LocalizedString* SerpentWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_SerpentWand::create();
}

std::string SerpentWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_SerpentWand;
}

std::string SerpentWand::getSerializationKey()
{
	return SerpentWand::SaveKey;
}

Vec2 SerpentWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* SerpentWand::getRecipe()
{
	return SerpentWandPlans::create();
}
