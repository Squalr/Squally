#include "DraksHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DraksHelm::SaveKeyDraksHelm = "draks-helm";

DraksHelm* DraksHelm::create()
{
	DraksHelm* instance = new DraksHelm();

	instance->autorelease();

	return instance;
}

DraksHelm::DraksHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

DraksHelm::~DraksHelm()
{
}

Item* DraksHelm::clone()
{
	return DraksHelm::create();
}

std::string DraksHelm::getItemName()
{
	return DraksHelm::SaveKeyDraksHelm;
}

LocalizedString* DraksHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_DraksHelm::create();
}

std::string DraksHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_DraksHelm;
}

std::string DraksHelm::getSerializationKey()
{
	return DraksHelm::SaveKeyDraksHelm;
}

Vec2 DraksHelm::getDisplayOffset()
{
	return Vec2(10.0f, -30.0f);
}
