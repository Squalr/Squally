#include "GarnetBand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GarnetBand::SaveKey = "garnet-band";

GarnetBand* GarnetBand::create()
{
	GarnetBand* instance = new GarnetBand();

	instance->autorelease();

	return instance;
}

GarnetBand::GarnetBand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 28 }}), ItemStats(
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

GarnetBand::~GarnetBand()
{
}

Item* GarnetBand::clone()
{
	return GarnetBand::create();
}

std::string GarnetBand::getItemName()
{
	return GarnetBand::SaveKey;
}

LocalizedString* GarnetBand::getString()
{
	return Strings::Items_Equipment_Gear_Rings_GarnetBand::create();
}

std::string GarnetBand::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings_GarnetBand;
}

std::string GarnetBand::getSerializationKey()
{
	return GarnetBand::SaveKey;
}
