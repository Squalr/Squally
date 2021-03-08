#include "HolyNecklace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HolyNecklace::SaveKey = "holy-necklace";

HolyNecklace* HolyNecklace::create()
{
	HolyNecklace* instance = new HolyNecklace();

	instance->autorelease();

	return instance;
}

HolyNecklace::HolyNecklace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	2,
	// Mana
	2,
	// Attack
	1,
	// Magic Attack
	1,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

HolyNecklace::~HolyNecklace()
{
}

Item* HolyNecklace::clone()
{
	return HolyNecklace::create();
}

const std::string& HolyNecklace::getItemName()
{
	return HolyNecklace::SaveKey;
}

LocalizedString* HolyNecklace::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_HolyNecklace::create();
}

const std::string& HolyNecklace::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_HolyNecklace;
}

const std::string& HolyNecklace::getIdentifier()
{
	return HolyNecklace::SaveKey;
}
