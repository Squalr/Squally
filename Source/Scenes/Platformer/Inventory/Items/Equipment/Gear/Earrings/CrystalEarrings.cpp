#include "CrystalEarrings.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalEarrings::SaveKey = "crystal-earrings";

CrystalEarrings* CrystalEarrings::create()
{
	CrystalEarrings* instance = new CrystalEarrings();

	instance->autorelease();

	return instance;
}

CrystalEarrings::CrystalEarrings() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 23 }}), ItemStats(
	// Health
	0,
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

CrystalEarrings::~CrystalEarrings()
{
}

Item* CrystalEarrings::clone()
{
	return CrystalEarrings::create();
}

const std::string& CrystalEarrings::getItemName()
{
	return CrystalEarrings::SaveKey;
}

LocalizedString* CrystalEarrings::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_CrystalEarrings::create();
}

const std::string& CrystalEarrings::getIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_CrystalEarrings;
}

const std::string& CrystalEarrings::getSerializationKey()
{
	return CrystalEarrings::SaveKey;
}
