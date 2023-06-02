#include "SilverRing.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Rings/SilverRingRecipe.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SilverRing::SaveKey = "silver-ring";

SilverRing* SilverRing::create()
{
	SilverRing* instance = new SilverRing();

	instance->autorelease();

	return instance;
}

// Tier 1
SilverRing::SilverRing() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 25 }}), ItemStats(
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

SilverRing::~SilverRing()
{
}

Item* SilverRing::clone()
{
	return SilverRing::create();
}

LocalizedString* SilverRing::getString()
{
	return Strings::Items_Equipment_Gear_Rings_SilverRing::create();
}

const std::string& SilverRing::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings_SilverRing;
}

const std::string& SilverRing::getIdentifier()
{
	return SilverRing::SaveKey;
}

Recipe* SilverRing::getRecipe()
{
	return SilverRingRecipe::create();
}
