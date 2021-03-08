#include "DraksHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DraksHelm::SaveKey = "draks-helm";

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
	// Magic Attack
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

const std::string& DraksHelm::getItemName()
{
	return DraksHelm::SaveKey;
}

LocalizedString* DraksHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_DraksHelm::create();
}

const std::string& DraksHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_DraksHelm;
}

const std::string& DraksHelm::getSerializationKey()
{
	return DraksHelm::SaveKey;
}

Vec2 DraksHelm::getDisplayOffset()
{
	return Vec2(10.0f, -30.0f);
}
