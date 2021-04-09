#include "WoodenShield.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Offhands/Shields/WoodenShieldPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenShield::SaveKey = "wooden-shield";

WoodenShield* WoodenShield::create()
{
	WoodenShield* instance = new WoodenShield();

	instance->autorelease();

	return instance;
}

WoodenShield::WoodenShield() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 3, 6, ItemStats(
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
	0.05f
))
{
}

WoodenShield::~WoodenShield()
{
}

Item* WoodenShield::clone()
{
	return WoodenShield::create();
}

LocalizedString* WoodenShield::getString()
{
	return Strings::Items_Equipment_Offhands_Shields_WoodenShield::create();
}

const std::string& WoodenShield::getIconResource()
{
	return ItemResources::Equipment_Gear_Offhands_Shields_WoodenShield;
}

const std::string& WoodenShield::getIdentifier()
{
	return WoodenShield::SaveKey;
}

Recipe* WoodenShield::getRecipe()
{
	return WoodenShieldPlans::create();
}
