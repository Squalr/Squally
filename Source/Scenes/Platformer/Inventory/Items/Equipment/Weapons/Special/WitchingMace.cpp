#include "WitchingMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/WitchingMacePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WitchingMace::SaveKey = "witching-mace";

WitchingMace* WitchingMace::create()
{
	WitchingMace* instance = new WitchingMace();

	instance->autorelease();

	return instance;
}

WitchingMace::WitchingMace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
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

WitchingMace::~WitchingMace()
{
}

Vec2 WitchingMace::getWeaponCollisionOffset()
{
	return Vec2(0.0f, 150.0f);
}

Item* WitchingMace::clone()
{
	return WitchingMace::create();
}

LocalizedString* WitchingMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_WitchingMace::create();
}

const std::string& WitchingMace::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_WitchingMace;
}

const std::string& WitchingMace::getIdentifier()
{
	return WitchingMace::SaveKey;
}

Vec2 WitchingMace::getDisplayOffset()
{
	return Vec2(4.0f, -10.0f);
}

Recipe* WitchingMace::getRecipe()
{
	return WitchingMacePlans::create();
}
