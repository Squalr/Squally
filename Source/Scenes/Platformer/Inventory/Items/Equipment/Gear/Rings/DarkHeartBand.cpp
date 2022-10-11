#include "DarkHeartBand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Rings/DarkHeartBandRecipe.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DarkHeartBand::SaveKey = "dark-heart-band";

DarkHeartBand* DarkHeartBand::create()
{
	DarkHeartBand* instance = new DarkHeartBand();

	instance->autorelease();

	return instance;
}

DarkHeartBand::DarkHeartBand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 28 }}), ItemStats(
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

DarkHeartBand::~DarkHeartBand()
{
}

Item* DarkHeartBand::clone()
{
	return DarkHeartBand::create();
}

LocalizedString* DarkHeartBand::getString()
{
	return Strings::Items_Equipment_Gear_Rings_DarkHeartBand::create();
}

const std::string& DarkHeartBand::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings_DarkHeartBand;
}

const std::string& DarkHeartBand::getIdentifier()
{
	return DarkHeartBand::SaveKey;
}

Recipe* DarkHeartBand::getRecipe()
{
	return DarkHeartBandRecipe::create();
}
