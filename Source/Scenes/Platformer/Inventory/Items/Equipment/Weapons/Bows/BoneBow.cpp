#include "BoneBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneBow::SaveKey = "bone-bow";

BoneBow* BoneBow::create()
{
	BoneBow* instance = new BoneBow();

	instance->autorelease();

	return instance;
}

BoneBow::BoneBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 48, 56, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.25f
))
{
}

BoneBow::~BoneBow()
{
}

Item* BoneBow::clone()
{
	return BoneBow::create();
}

std::string BoneBow::getItemName()
{
	return BoneBow::SaveKey;
}

LocalizedString* BoneBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_BoneBow::create();
}

std::string BoneBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_BoneBow;
}

std::string BoneBow::getSerializationKey()
{
	return BoneBow::SaveKey;
}

Vec2 BoneBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
