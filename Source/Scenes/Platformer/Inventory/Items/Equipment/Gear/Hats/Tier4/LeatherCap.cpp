#include "LeatherCap.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

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

LeatherCap::~LeatherCap()
{
}

Item* LeatherCap::clone()
{
	return LeatherCap::create();
}

const std::string& LeatherCap::getItemName()
{
	return LeatherCap::SaveKey;
}

LocalizedString* LeatherCap::getString()
{
	return Strings::Items_Equipment_Gear_Hats_LeatherCap::create();
}

const std::string& LeatherCap::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_LeatherCap;
}

const std::string& LeatherCap::getIdentifier()
{
	return LeatherCap::SaveKey;
}

Vec2 LeatherCap::getDisplayOffset()
{
	return Vec2(2.0f, -38.0f);
}
