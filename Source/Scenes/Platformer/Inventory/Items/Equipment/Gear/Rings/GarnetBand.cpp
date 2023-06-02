#include "GarnetBand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Rings/GarnetBandRecipe.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GarnetBand::SaveKey = "garnet-band";

GarnetBand* GarnetBand::create()
{
	GarnetBand* instance = new GarnetBand();

	instance->autorelease();

	return instance;
}

// Tier 1
GarnetBand::GarnetBand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 25 }}), ItemStats(
	// Health
	1,
	// Mana
	3,
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

GarnetBand::~GarnetBand()
{
}

Item* GarnetBand::clone()
{
	return GarnetBand::create();
}

LocalizedString* GarnetBand::getString()
{
	return Strings::Items_Equipment_Gear_Rings_GarnetBand::create();
}

const std::string& GarnetBand::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings_GarnetBand;
}

const std::string& GarnetBand::getIdentifier()
{
	return GarnetBand::SaveKey;
}

Recipe* GarnetBand::getRecipe()
{
	return GarnetBandRecipe::create();
}
