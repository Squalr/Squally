#include "MarineBand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MarineBand::SaveKey = "marine-band";

MarineBand* MarineBand::create()
{
	MarineBand* instance = new MarineBand();

	instance->autorelease();

	return instance;
}

MarineBand::MarineBand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 28 }}), ItemStats(
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

MarineBand::~MarineBand()
{
}

Item* MarineBand::clone()
{
	return MarineBand::create();
}

std::string MarineBand::getItemName()
{
	return MarineBand::SaveKey;
}

LocalizedString* MarineBand::getString()
{
	return Strings::Items_Equipment_Gear_Rings_MarineBand::create();
}

std::string MarineBand::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings_MarineBand;
}

std::string MarineBand::getSerializationKey()
{
	return MarineBand::SaveKey;
}
