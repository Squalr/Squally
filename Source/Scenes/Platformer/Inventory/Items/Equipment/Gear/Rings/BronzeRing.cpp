#include "BronzeRing.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Rings/BronzeRingRecipe.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BronzeRing::SaveKey = "bronze-ring";

BronzeRing* BronzeRing::create()
{
	BronzeRing* instance = new BronzeRing();

	instance->autorelease();

	return instance;
}

// Tier 0
BronzeRing::BronzeRing() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
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

BronzeRing::~BronzeRing()
{
}

Item* BronzeRing::clone()
{
	return BronzeRing::create();
}

LocalizedString* BronzeRing::getString()
{
	return Strings::Items_Equipment_Gear_Rings_BronzeRing::create();
}

const std::string& BronzeRing::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings__Deprecated_T0_BronzeRing;
}

const std::string& BronzeRing::getIdentifier()
{
	return BronzeRing::SaveKey;
}

Recipe* BronzeRing::getRecipe()
{
	return BronzeRingRecipe::create();
}
