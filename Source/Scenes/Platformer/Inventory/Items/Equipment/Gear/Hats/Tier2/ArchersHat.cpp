#include "ArchersHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier2/ArchersHatPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ArchersHat::SaveKey = "archers-hat";

ArchersHat* ArchersHat::create()
{
	ArchersHat* instance = new ArchersHat();

	instance->autorelease();

	return instance;
}

ArchersHat::ArchersHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	2,
	// Mana
	2,
	// Attack
	1,
	// Magic Attack
	1,
	// Armor
	2,
	// Speed
	0.05f
))
{
}

ArchersHat::~ArchersHat()
{
}

Item* ArchersHat::clone()
{
	return ArchersHat::create();
}

LocalizedString* ArchersHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_ArchersHat::create();
}

const std::string& ArchersHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_ArchersHat;
}

const std::string& ArchersHat::getIdentifier()
{
	return ArchersHat::SaveKey;
}

Vec2 ArchersHat::getDisplayOffset()
{
	return Vec2(2.0f, -10.0f);
}

Recipe* ArchersHat::getRecipe()
{
	return ArchersHatPlans::create();
}
