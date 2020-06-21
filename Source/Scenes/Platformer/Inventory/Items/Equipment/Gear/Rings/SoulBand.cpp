#include "SoulBand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SoulBand::SaveKey = "soul-band";

SoulBand* SoulBand::create()
{
	SoulBand* instance = new SoulBand();

	instance->autorelease();

	return instance;
}

SoulBand::SoulBand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 28 }}), ItemStats(
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

SoulBand::~SoulBand()
{
}

Item* SoulBand::clone()
{
	return SoulBand::create();
}

std::string SoulBand::getItemName()
{
	return SoulBand::SaveKey;
}

LocalizedString* SoulBand::getString()
{
	return Strings::Items_Equipment_Gear_Rings_SoulBand::create();
}

std::string SoulBand::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings_SoulBand;
}

std::string SoulBand::getSerializationKey()
{
	return SoulBand::SaveKey;
}
