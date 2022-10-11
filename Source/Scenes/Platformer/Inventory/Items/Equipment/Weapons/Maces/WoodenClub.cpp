#include "WoodenClub.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/WoodenClubPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenClub::SaveKey = "wooden-club";

WoodenClub* WoodenClub::create()
{
	WoodenClub* instance = new WoodenClub();

	instance->autorelease();

	return instance;
}

WoodenClub::WoodenClub() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 5, 7, ItemStats(
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

WoodenClub::~WoodenClub()
{
}

Item* WoodenClub::clone()
{
	return WoodenClub::create();
}

LocalizedString* WoodenClub::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_WoodenClub::create();
}

const std::string& WoodenClub::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_WoodenClub;
}

const std::string& WoodenClub::getIdentifier()
{
	return WoodenClub::SaveKey;
}

Vec2 WoodenClub::getDisplayOffset()
{
	return Vec2(-4.0f, -2.0f);
}

Recipe* WoodenClub::getRecipe()
{
	return WoodenClubPlans::create();
}
