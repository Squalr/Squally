#include "GunnersHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier4/GunnersHatPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GunnersHat::SaveKey = "gunners-hat";

GunnersHat* GunnersHat::create()
{
	GunnersHat* instance = new GunnersHat();

	instance->autorelease();

	return instance;
}

GunnersHat::GunnersHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

GunnersHat::~GunnersHat()
{
}

Item* GunnersHat::clone()
{
	return GunnersHat::create();
}

LocalizedString* GunnersHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_GunnersHat::create();
}

const std::string& GunnersHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_GunnersHat;
}

const std::string& GunnersHat::getIdentifier()
{
	return GunnersHat::SaveKey;
}

Vec2 GunnersHat::getDisplayOffset()
{
	return Vec2(0.0f, -26.0f);
}

Recipe* GunnersHat::getRecipe()
{
	return GunnersHatPlans::create();
}
