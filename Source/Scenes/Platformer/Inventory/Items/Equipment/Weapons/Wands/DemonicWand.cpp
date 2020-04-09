#include "DemonicWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonicWand::SaveKey = "demonic-wand";

DemonicWand* DemonicWand::create()
{
	DemonicWand* instance = new DemonicWand();

	instance->autorelease();

	return instance;
}

DemonicWand::DemonicWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 12, 16, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.15f
))
{
}

DemonicWand::~DemonicWand()
{
}

Item* DemonicWand::clone()
{
	return DemonicWand::create();
}

std::string DemonicWand::getItemName()
{
	return DemonicWand::SaveKey;
}

LocalizedString* DemonicWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_DemonicWand::create();
}

std::string DemonicWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_DemonicWand;
}

std::string DemonicWand::getSerializationKey()
{
	return DemonicWand::SaveKey;
}

Vec2 DemonicWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
