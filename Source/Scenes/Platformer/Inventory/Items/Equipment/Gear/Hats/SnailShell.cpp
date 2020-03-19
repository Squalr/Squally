#include "SnailShell.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SnailShell::SaveKey = "snail-shell";

SnailShell* SnailShell::create()
{
	SnailShell* instance = new SnailShell();

	instance->autorelease();

	return instance;
}

SnailShell::SnailShell() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

SnailShell::~SnailShell()
{
}

Item* SnailShell::clone()
{
	return SnailShell::create();
}

std::string SnailShell::getItemName()
{
	return SnailShell::SaveKey;
}

LocalizedString* SnailShell::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SnailShell::create();
}

std::string SnailShell::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_SnailShell;
}

std::string SnailShell::getSerializationKey()
{
	return SnailShell::SaveKey;
}

Vec2 SnailShell::getDisplayOffset()
{
	return Vec2(-36.0f, -34.0f);
}
