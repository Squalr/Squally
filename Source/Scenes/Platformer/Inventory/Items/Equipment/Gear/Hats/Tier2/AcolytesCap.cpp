#include "AcolytesCap.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier2/AcolytesCapPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AcolytesCap::SaveKey = "acolytes-cap";

AcolytesCap* AcolytesCap::create()
{
	AcolytesCap* instance = new AcolytesCap();

	instance->autorelease();

	return instance;
}

AcolytesCap::AcolytesCap() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	0,
	// Mana
	3,
	// Attack
	0,
	// Magic Attack
	3,
	// Armor
	1,
	// Speed
	0.05f
))
{
}

AcolytesCap::~AcolytesCap()
{
}

Item* AcolytesCap::clone()
{
	return AcolytesCap::create();
}

LocalizedString* AcolytesCap::getString()
{
	return Strings::Items_Equipment_Gear_Hats_AcolytesCap::create();
}

const std::string& AcolytesCap::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_AcolytesCap;
}

const std::string& AcolytesCap::getIdentifier()
{
	return AcolytesCap::SaveKey;
}

Vec2 AcolytesCap::getDisplayOffset()
{
	return Vec2(26.0f, -38.0f);
}

Recipe* AcolytesCap::getRecipe()
{
	return AcolytesCapPlans::create();
}
