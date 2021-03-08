#include "WoodenSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/WoodenSwordPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenSword::SaveKey = "wooden-sword";

WoodenSword* WoodenSword::create()
{
	WoodenSword* instance = new WoodenSword();

	instance->autorelease();

	return instance;
}

WoodenSword::WoodenSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 9 }}), 4, 6, ItemStats(
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

WoodenSword::~WoodenSword()
{
}

Item* WoodenSword::clone()
{
	return WoodenSword::create();
}

const std::string& WoodenSword::getItemName()
{
	return WoodenSword::SaveKey;
}

LocalizedString* WoodenSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_WoodenSword::create();
}

const std::string& WoodenSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_WoodenSword;
}

const std::string& WoodenSword::getIdentifier()
{
	return WoodenSword::SaveKey;
}

Recipe* WoodenSword::getRecipe()
{
	return WoodenSwordPlans::create();
}
