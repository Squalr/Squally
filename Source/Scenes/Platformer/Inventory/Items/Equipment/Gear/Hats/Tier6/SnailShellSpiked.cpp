#include "SnailShellSpiked.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

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
	return ItemResources::Equipment_Gear_Hats_SnailShellSpiked;
}

const std::string& SnailShellSpiked::getIdentifier()
{
	return SnailShellSpiked::SaveKey;
}

Vec2 SnailShellSpiked::getDisplayOffset()
{
	return Vec2(-36.0f, -34.0f);
}
