#include "TigersBane.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TigersBane::SaveKeyTigersBane = "tigers-bane";

TigersBane* TigersBane::create()
{
	TigersBane* instance = new TigersBane();

	instance->autorelease();

	return instance;
}

TigersBane::TigersBane() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

TigersBane::~TigersBane()
{
}

Item* TigersBane::clone()
{
	return TigersBane::create();
}

std::string TigersBane::getItemName()
{
	return TigersBane::SaveKeyTigersBane;
}

LocalizedString* TigersBane::getString()
{
	return Strings::Items_Equipment_Gear_Hats_TigersBane::create();
}

std::string TigersBane::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_TigersBane;
}

std::string TigersBane::getSerializationKey()
{
	return TigersBane::SaveKeyTigersBane;
}

Vec2 TigersBane::getDisplayOffset()
{
	return Vec2(12.0f, -18.0f);
}
