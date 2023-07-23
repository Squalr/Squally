#include "SantaHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier7/SantaHatPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SantaHat::SaveKey = "santa-hat";

SantaHat* SantaHat::create()
{
	SantaHat* instance = new SantaHat();

	instance->autorelease();

	return instance;
}

SantaHat::SantaHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	ARCHER_HP(7),
	// Mana
	ARCHER_MP(7),
	// Attack
	ARCHER_ATTACK(7),
	// Magic Attack
	ARCHER_MAGIC_ATTACK(7),
	// Armor
	ARCHER_ARMOR(7),
	// Speed
	ARCHER_SPEED(7)
))
{
}

SantaHat::~SantaHat()
{
}

Item* SantaHat::clone()
{
	return SantaHat::create();
}

LocalizedString* SantaHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

const std::string& SantaHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier7_SantaHat;
}

const std::string& SantaHat::getIdentifier()
{
	return SantaHat::SaveKey;
}

Vec2 SantaHat::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}

Recipe* SantaHat::getRecipe()
{
	return SantaHatPlans::create();
}
