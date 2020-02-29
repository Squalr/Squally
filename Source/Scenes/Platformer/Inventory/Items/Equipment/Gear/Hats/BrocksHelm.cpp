#include "BrocksHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BrocksHelm::SaveKeyBrocksHelm = "brocks-helm";

BrocksHelm* BrocksHelm::create()
{
	BrocksHelm* instance = new BrocksHelm();

	instance->autorelease();

	return instance;
}

BrocksHelm::BrocksHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

BrocksHelm::~BrocksHelm()
{
}

Item* BrocksHelm::clone()
{
	return BrocksHelm::create();
}

std::string BrocksHelm::getItemName()
{
	return BrocksHelm::SaveKeyBrocksHelm;
}

LocalizedString* BrocksHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string BrocksHelm::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_BrocksHelm;
}

std::string BrocksHelm::getSerializationKey()
{
	return BrocksHelm::SaveKeyBrocksHelm;
}

Vec2 BrocksHelm::getDisplayOffset()
{
	return Vec2(-6.0f, -20.0f);
}
