#include "TigersBane.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TigersBane::SaveKey = "tigers-bane";

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
	// Magic Attack
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

const std::string& TigersBane::getItemName()
{
	return TigersBane::SaveKey;
}

LocalizedString* TigersBane::getString()
{
	return Strings::Items_Equipment_Gear_Hats_TigersBane::create();
}

const std::string& TigersBane::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_TigersBane;
}

const std::string& TigersBane::getIdentifier()
{
	return TigersBane::SaveKey;
}

Vec2 TigersBane::getDisplayOffset()
{
	return Vec2(12.0f, -18.0f);
}
