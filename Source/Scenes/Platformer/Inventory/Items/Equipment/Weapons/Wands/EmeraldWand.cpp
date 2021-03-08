#include "EmeraldWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/EmeraldWandPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EmeraldWand::SaveKey = "emerald-wand";

EmeraldWand* EmeraldWand::create()
{
	EmeraldWand* instance = new EmeraldWand();

	instance->autorelease();

	return instance;
}

EmeraldWand::EmeraldWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 7, 8, ItemStats(
	// Health
	0,
	// Mana
	10,
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

EmeraldWand::~EmeraldWand()
{
}

Item* EmeraldWand::clone()
{
	return EmeraldWand::create();
}

const std::string& EmeraldWand::getItemName()
{
	return EmeraldWand::SaveKey;
}

LocalizedString* EmeraldWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_EmeraldWand::create();
}

const std::string& EmeraldWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_EmeraldWand;
}

const std::string& EmeraldWand::getIdentifier()
{
	return EmeraldWand::SaveKey;
}

Vec2 EmeraldWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* EmeraldWand::getRecipe()
{
	return EmeraldWandPlans::create();
}
