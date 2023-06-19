#include "SnailShellSpiked.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier6/SnailShellSpikedPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SnailShellSpiked::SaveKey = "snail-shell-spiked";

SnailShellSpiked* SnailShellSpiked::create()
{
	SnailShellSpiked* instance = new SnailShellSpiked();

	instance->autorelease();

	return instance;
}

SnailShellSpiked::SnailShellSpiked() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	ARCHER_HP(6),
	// Mana
	ARCHER_MP(6),
	// Attack
	ARCHER_ATTACK(6),
	// Magic Attack
	ARCHER_MAGIC_ATTACK(6),
	// Armor
	ARCHER_ARMOR(6),
	// Speed
	ARCHER_SPEED(6)
))
{
}

SnailShellSpiked::~SnailShellSpiked()
{
}

Item* SnailShellSpiked::clone()
{
	return SnailShellSpiked::create();
}

LocalizedString* SnailShellSpiked::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SnailShellSpiked::create();
}

const std::string& SnailShellSpiked::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier6_SnailShellSpiked;
}

const std::string& SnailShellSpiked::getIdentifier()
{
	return SnailShellSpiked::SaveKey;
}

Vec2 SnailShellSpiked::getDisplayOffset()
{
	return Vec2(-36.0f, -34.0f);
}

Recipe* SnailShellSpiked::getRecipe()
{
	return SnailShellSpikedPlans::create();
}
