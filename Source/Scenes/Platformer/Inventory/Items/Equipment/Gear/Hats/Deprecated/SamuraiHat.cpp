#include "SamuraiHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SamuraiHat::SaveKey = "samurai-hat";

SamuraiHat* SamuraiHat::create()
{
	SamuraiHat* instance = new SamuraiHat();

	instance->autorelease();

	return instance;
}

SamuraiHat::SamuraiHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

SamuraiHat::~SamuraiHat()
{
}

Item* SamuraiHat::clone()
{
	return SamuraiHat::create();
}

LocalizedString* SamuraiHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SamuraiHat::create();
}

const std::string& SamuraiHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_SamuraiHat;
}

const std::string& SamuraiHat::getIdentifier()
{
	return SamuraiHat::SaveKey;
}

Vec2 SamuraiHat::getDisplayOffset()
{
	return Vec2(-18.0f, -10.0f);
}

Recipe* SamuraiHat::getRecipe()
{
	return nullptr;
}
