#include "WoodenPikeHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenPikeHelm::SaveKeyWoodenPikeHelm = "wooden-pike-helm";

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

std::string WoodenPikeHelm::getItemName()
{
	return WoodenPikeHelm::SaveKeyWoodenPikeHelm;
}

LocalizedString* WoodenPikeHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string WoodenPikeHelm::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_WoodenPikeHelm;
}

std::string WoodenPikeHelm::getSerializationKey()
{
	return WoodenPikeHelm::SaveKeyWoodenPikeHelm;
}

Vec2 WoodenPikeHelm::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
