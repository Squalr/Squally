#include "BarbedHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BarbedHelm::SaveKey = "barbed-helm";

BarbedHelm* BarbedHelm::create()
{
	BarbedHelm* instance = new BarbedHelm();

	instance->autorelease();

	return instance;
}

BarbedHelm::BarbedHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

BarbedHelm::~BarbedHelm()
{
}

Item* BarbedHelm::clone()
{
	return BarbedHelm::create();
}

std::string BarbedHelm::getItemName()
{
	return BarbedHelm::SaveKey;
}

LocalizedString* BarbedHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_BarbedHelm::create();
}

std::string BarbedHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_BarbedHelm;
}

std::string BarbedHelm::getSerializationKey()
{
	return BarbedHelm::SaveKey;
}

Vec2 BarbedHelm::getDisplayOffset()
{
	return Vec2(-24.0f, -4.0f);
}
