#include "LeatherCap.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier4/LeatherCapPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LeatherCap::SaveKey = "leather-cap";

LeatherCap* LeatherCap::create()
{
	LeatherCap* instance = new LeatherCap();

	instance->autorelease();

	return instance;
}

LeatherCap::LeatherCap() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	ARCHER_HP(4),
	// Mana
	ARCHER_MP(4),
	// Attack
	ARCHER_ATTACK(4),
	// Magic Attack
	ARCHER_MAGIC_ATTACK(4),
	// Armor
	ARCHER_ARMOR(4),
	// Speed
	ARCHER_SPEED(4)
))
{
}

LeatherCap::~LeatherCap()
{
}

Item* LeatherCap::clone()
{
	return LeatherCap::create();
}

LocalizedString* LeatherCap::getString()
{
	return Strings::Items_Equipment_Gear_Hats_LeatherCap::create();
}

const std::string& LeatherCap::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier4_LeatherCap;
}

const std::string& LeatherCap::getIdentifier()
{
	return LeatherCap::SaveKey;
}

Vec2 LeatherCap::getDisplayOffset()
{
	return Vec2(2.0f, -38.0f);
}

Recipe* LeatherCap::getRecipe()
{
	return LeatherCapPlans::create();
}
