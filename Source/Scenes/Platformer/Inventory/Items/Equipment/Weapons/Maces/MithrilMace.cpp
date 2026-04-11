#include "MithrilMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/MithrilMacePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilMace::SaveKey = "mithril-mace";

MithrilMace* MithrilMace::create()
{
	MithrilMace* instance = new MithrilMace();

	instance->autorelease();

	return instance;
}

MithrilMace::MithrilMace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), MACE_DAMAGE_MIN(5), MACE_DAMAGE_MAX(5), ItemStats(
	// Health
	1,
	// Mana
	1,
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

MithrilMace::~MithrilMace()
{
}

Vec2 MithrilMace::getWeaponCollisionOffset()
{
	return Vec2(0.0f, 40.0f);
}

Vec2 MithrilMace::getDisplayOffset()
{
	return Vec2(0.0f, -12.0f);
}

Item* MithrilMace::clone()
{
	return MithrilMace::create();
}

LocalizedString* MithrilMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_MithrilMace::create();
}

const std::string& MithrilMace::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_MithrilMace;
}

const std::string& MithrilMace::getIdentifier()
{
	return MithrilMace::SaveKey;
}

Recipe* MithrilMace::getRecipe()
{
	return MithrilMacePlans::create();
}
