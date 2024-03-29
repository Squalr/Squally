#include "WoodenWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/WoodenWandPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenWand::SaveKey = "wooden-wand";

WoodenWand* WoodenWand::create()
{
	WoodenWand* instance = new WoodenWand();

	instance->autorelease();

	return instance;
}

WoodenWand::WoodenWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), WAND_DAMAGE_MIN(1), WAND_DAMAGE_MAX(1), ItemStats(
	// Health
	0,
	// Mana
	4,
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

WoodenWand::~WoodenWand()
{
}

Item* WoodenWand::clone()
{
	return WoodenWand::create();
}

LocalizedString* WoodenWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_WoodenWand::create();
}

const std::string& WoodenWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_WoodenWand;
}

const std::string& WoodenWand::getIdentifier()
{
	return WoodenWand::SaveKey;
}

Vec2 WoodenWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* WoodenWand::getRecipe()
{
	return WoodenWandPlans::create();
}
