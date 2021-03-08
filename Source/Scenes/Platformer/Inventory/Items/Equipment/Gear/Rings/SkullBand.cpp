#include "SkullBand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkullBand::SaveKey = "skull-band";

SkullBand* SkullBand::create()
{
	SkullBand* instance = new SkullBand();

	instance->autorelease();

	return instance;
}

SkullBand::SkullBand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 28 }}), ItemStats(
	// Health
	2,
	// Mana
	2,
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

SkullBand::~SkullBand()
{
}

Item* SkullBand::clone()
{
	return SkullBand::create();
}

const std::string& SkullBand::getItemName()
{
	return SkullBand::SaveKey;
}

LocalizedString* SkullBand::getString()
{
	return Strings::Items_Equipment_Gear_Rings_SkullBand::create();
}

const std::string& SkullBand::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings_SkullBand;
}

const std::string& SkullBand::getSerializationKey()
{
	return SkullBand::SaveKey;
}
