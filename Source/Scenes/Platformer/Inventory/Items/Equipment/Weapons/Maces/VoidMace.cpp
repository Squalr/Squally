#include "VoidMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/VoidMacePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidMace::SaveKey = "void-mace";

VoidMace* VoidMace::create()
{
	VoidMace* instance = new VoidMace();

	instance->autorelease();

	return instance;
}

VoidMace::VoidMace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), MACE_DAMAGE_MIN(9), MACE_DAMAGE_MAX(9), ItemStats(
	// Health
	8,
	// Mana
	3,
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

VoidMace::~VoidMace()
{
}

Item* VoidMace::clone()
{
	return VoidMace::create();
}

LocalizedString* VoidMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_VoidMace::create();
}

const std::string& VoidMace::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_VoidMace;
}

const std::string& VoidMace::getIdentifier()
{
	return VoidMace::SaveKey;
}

Vec2 VoidMace::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* VoidMace::getRecipe()
{
	return VoidMacePlans::create();
}
