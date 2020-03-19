#include "DemonShell.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonShell::SaveKey = "demon-shell";

DemonShell* DemonShell::create()
{
	DemonShell* instance = new DemonShell();

	instance->autorelease();

	return instance;
}

DemonShell::DemonShell() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

DemonShell::~DemonShell()
{
}

Item* DemonShell::clone()
{
	return DemonShell::create();
}

std::string DemonShell::getItemName()
{
	return DemonShell::SaveKey;
}

LocalizedString* DemonShell::getString()
{
	return Strings::Items_Equipment_Gear_Hats_DemonShell::create();
}

std::string DemonShell::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_DemonShell;
}

std::string DemonShell::getSerializationKey()
{
	return DemonShell::SaveKey;
}

Vec2 DemonShell::getDisplayOffset()
{
	return Vec2(6.0f, -34.0f);
}
