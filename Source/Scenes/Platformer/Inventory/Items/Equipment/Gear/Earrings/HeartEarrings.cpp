#include "HeartEarrings.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HeartEarrings::SaveKey = "heart-earrings";

HeartEarrings* HeartEarrings::create()
{
	HeartEarrings* instance = new HeartEarrings();

	instance->autorelease();

	return instance;
}

HeartEarrings::HeartEarrings() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 23 }}), ItemStats(
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

HeartEarrings::~HeartEarrings()
{
}

Item* HeartEarrings::clone()
{
	return HeartEarrings::create();
}

const std::string& HeartEarrings::getItemName()
{
	return HeartEarrings::SaveKey;
}

LocalizedString* HeartEarrings::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_HeartEarrings::create();
}

const std::string& HeartEarrings::getIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_HeartEarrings;
}

const std::string& HeartEarrings::getSerializationKey()
{
	return HeartEarrings::SaveKey;
}
