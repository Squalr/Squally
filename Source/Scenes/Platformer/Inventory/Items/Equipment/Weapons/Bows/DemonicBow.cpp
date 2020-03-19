#include "DemonicBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonicBow::SaveKey = "demonic-bow";

DemonicBow* DemonicBow::create()
{
	DemonicBow* instance = new DemonicBow();

	instance->autorelease();

	return instance;
}

DemonicBow::DemonicBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 16, 24, ItemStats(
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

DemonicBow::~DemonicBow()
{
}

Item* DemonicBow::clone()
{
	return DemonicBow::create();
}

std::string DemonicBow::getItemName()
{
	return DemonicBow::SaveKey;
}

LocalizedString* DemonicBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_DemonicBow::create();
}

std::string DemonicBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_DemonicBow;
}

std::string DemonicBow::getSerializationKey()
{
	return DemonicBow::SaveKey;
}

Vec2 DemonicBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
