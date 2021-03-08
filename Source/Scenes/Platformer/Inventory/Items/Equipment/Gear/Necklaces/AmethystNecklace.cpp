#include "AmethystNecklace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AmethystNecklace::SaveKey = "amethyst-necklace";

AmethystNecklace* AmethystNecklace::create()
{
	AmethystNecklace* instance = new AmethystNecklace();

	instance->autorelease();

	return instance;
}

AmethystNecklace::AmethystNecklace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 63 }}), ItemStats(
	// Health
	3,
	// Mana
	3,
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

AmethystNecklace::~AmethystNecklace()
{
}

Item* AmethystNecklace::clone()
{
	return AmethystNecklace::create();
}

const std::string& AmethystNecklace::getItemName()
{
	return AmethystNecklace::SaveKey;
}

LocalizedString* AmethystNecklace::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_AmethystNecklace::create();
}

const std::string& AmethystNecklace::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_AmethystNecklace;
}

const std::string& AmethystNecklace::getIdentifier()
{
	return AmethystNecklace::SaveKey;
}
