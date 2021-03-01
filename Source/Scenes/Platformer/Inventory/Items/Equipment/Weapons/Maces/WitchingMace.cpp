#include "WitchingMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/WitchingMacePlans.h"

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

Item* WitchingMace::clone()
{
	return WitchingMace::create();
}

std::string WitchingMace::getItemName()
{
	return WitchingMace::SaveKey;
}

LocalizedString* WitchingMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_WitchingMace::create();
}

std::string WitchingMace::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_WitchingMace;
}

std::string WitchingMace::getSerializationKey()
{
	return WitchingMace::SaveKey;
}

Vec2 WitchingMace::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* WitchingMace::getRecipe()
{
	return WitchingMacePlans::create();
}
