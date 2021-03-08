#include "SapphireEarrings.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SapphireEarrings::SaveKey = "sapphire-earrings";

SapphireEarrings* SapphireEarrings::create()
{
	SapphireEarrings* instance = new SapphireEarrings();

	instance->autorelease();

	return instance;
}

SapphireEarrings::SapphireEarrings() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
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

SapphireEarrings::~SapphireEarrings()
{
}

Item* SapphireEarrings::clone()
{
	return SapphireEarrings::create();
}

LocalizedString* SapphireEarrings::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_SapphireEarrings::create();
}

const std::string& SapphireEarrings::getIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_SapphireEarrings;
}

const std::string& SapphireEarrings::getIdentifier()
{
	return SapphireEarrings::SaveKey;
}
