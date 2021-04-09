#include "PriestHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier7/PriestHatPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PriestHat::SaveKey = "priest-hat";

PriestHat* PriestHat::create()
{
	PriestHat* instance = new PriestHat();

	instance->autorelease();

	return instance;
}

PriestHat::PriestHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	0,
	// Mana
	0,
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

PriestHat::~PriestHat()
{
}

Item* PriestHat::clone()
{
	return PriestHat::create();
}

LocalizedString* PriestHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_PriestHat::create();
}

const std::string& PriestHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_PriestHat;
}

const std::string& PriestHat::getIdentifier()
{
	return PriestHat::SaveKey;
}

Vec2 PriestHat::getDisplayOffset()
{
	return Vec2(-10.0f, 24.0f);
}

Recipe* PriestHat::getRecipe()
{
	return PriestHatPlans::create();
}
