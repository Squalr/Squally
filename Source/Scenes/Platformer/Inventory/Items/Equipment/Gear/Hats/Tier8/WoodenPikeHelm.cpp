#include "WoodenPikeHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenPikeHelm::SaveKey = "wooden-pike-helm";

WoodenPikeHelm* WoodenPikeHelm::create()
{
	WoodenPikeHelm* instance = new WoodenPikeHelm();

	instance->autorelease();

	return instance;
}

WoodenPikeHelm::WoodenPikeHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

WoodenPikeHelm::~WoodenPikeHelm()
{
}

Item* WoodenPikeHelm::clone()
{
	return WoodenPikeHelm::create();
}

const std::string& WoodenPikeHelm::getItemName()
{
	return WoodenPikeHelm::SaveKey;
}

LocalizedString* WoodenPikeHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WoodenPikeHelm::create();
}

const std::string& WoodenPikeHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WoodenPikeHelm;
}

const std::string& WoodenPikeHelm::getIdentifier()
{
	return WoodenPikeHelm::SaveKey;
}

Vec2 WoodenPikeHelm::getDisplayOffset()
{
	return Vec2(22.0f, 20.0f);
}
