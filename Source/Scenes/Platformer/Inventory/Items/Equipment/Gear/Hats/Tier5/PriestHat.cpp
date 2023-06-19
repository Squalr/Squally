#include "PriestHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier5/PriestHatPlans.h"

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
	MAGE_HP(5),
	// Mana
	MAGE_MP(5),
	// Attack
	MAGE_ATTACK(5),
	// Magic Attack
	MAGE_MAGIC_ATTACK(5),
	// Armor
	MAGE_ARMOR(5),
	// Speed
	MAGE_SPEED(5)
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
	return ItemResources::Equipment_Gear_Hats_Tier5_PriestHat;
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
