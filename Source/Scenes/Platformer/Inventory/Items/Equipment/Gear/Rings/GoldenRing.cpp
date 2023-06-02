#include "GoldenRing.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Rings/GoldenRingRecipe.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenRing::SaveKey = "silver-ring";

GoldenRing* GoldenRing::create()
{
	GoldenRing* instance = new GoldenRing();

	instance->autorelease();

	return instance;
}

// Tier 2
GoldenRing::GoldenRing() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 35 }}), ItemStats(
	// Health
	2,
	// Mana
	4,
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

GoldenRing::~GoldenRing()
{
}

Item* GoldenRing::clone()
{
	return GoldenRing::create();
}

LocalizedString* GoldenRing::getString()
{
	return Strings::Items_Equipment_Gear_Rings_GoldenRing::create();
}

const std::string& GoldenRing::getIconResource()
{
	return ItemResources::Equipment_Gear_Rings_GoldenRing;
}

const std::string& GoldenRing::getIdentifier()
{
	return GoldenRing::SaveKey;
}

Recipe* GoldenRing::getRecipe()
{
	return GoldenRingRecipe::create();
}
