#include "MarineNecklace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MarineNecklace::SaveKey = "marine-necklace";

MarineNecklace* MarineNecklace::create()
{
	MarineNecklace* instance = new MarineNecklace();

	instance->autorelease();

	return instance;
}

MarineNecklace::MarineNecklace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 63 }}), ItemStats(
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

MarineNecklace::~MarineNecklace()
{
}

Item* MarineNecklace::clone()
{
	return MarineNecklace::create();
}

const std::string& MarineNecklace::getItemName()
{
	return MarineNecklace::SaveKey;
}

LocalizedString* MarineNecklace::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_MarineNecklace::create();
}

const std::string& MarineNecklace::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_MarineNecklace;
}

const std::string& MarineNecklace::getSerializationKey()
{
	return MarineNecklace::SaveKey;
}
