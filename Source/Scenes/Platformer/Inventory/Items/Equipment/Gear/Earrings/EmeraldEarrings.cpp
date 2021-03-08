#include "EmeraldEarrings.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EmeraldEarrings::SaveKey = "emerald-earrings";

EmeraldEarrings* EmeraldEarrings::create()
{
	EmeraldEarrings* instance = new EmeraldEarrings();

	instance->autorelease();

	return instance;
}

EmeraldEarrings::EmeraldEarrings() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 23 }}), ItemStats(
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

EmeraldEarrings::~EmeraldEarrings()
{
}

Item* EmeraldEarrings::clone()
{
	return EmeraldEarrings::create();
}

const std::string& EmeraldEarrings::getItemName()
{
	return EmeraldEarrings::SaveKey;
}

LocalizedString* EmeraldEarrings::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_EmeraldEarrings::create();
}

const std::string& EmeraldEarrings::getIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_EmeraldEarrings;
}

const std::string& EmeraldEarrings::getIdentifier()
{
	return EmeraldEarrings::SaveKey;
}
