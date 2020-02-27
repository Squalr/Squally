#include "WarBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WarBow::SaveKeyWarBow = "war-bow";

WarBow* WarBow::create()
{
	WarBow* instance = new WarBow();

	instance->autorelease();

	return instance;
}

WarBow::WarBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 16, 24, ItemStats(
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

WarBow::~WarBow()
{
}

Item* WarBow::clone()
{
	return WarBow::create();
}

std::string WarBow::getItemName()
{
	return WarBow::SaveKeyWarBow;
}

LocalizedString* WarBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_WarBow::create();
}

std::string WarBow::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_WarBow;
}

std::string WarBow::getSerializationKey()
{
	return WarBow::SaveKeyWarBow;
}

Vec2 WarBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
