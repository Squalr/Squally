#include "Scythe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/ScythePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Scythe::SaveKey = "scythe";

Scythe* Scythe::create()
{
	Scythe* instance = new Scythe();

	instance->autorelease();

	return instance;
}

Scythe::Scythe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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
	0.10f
))
{
}

Scythe::~Scythe()
{
}

Item* Scythe::clone()
{
	return Scythe::create();
}

LocalizedString* Scythe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_Scythe::create();
}

const std::string& Scythe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_Scythe;
}

const std::string& Scythe::getIdentifier()
{
	return Scythe::SaveKey;
}

CSize Scythe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return CSize(112.0f, 96.0f);
}

Vec2 Scythe::getWeaponCollisionOffset()
{
	return Vec2(32.0f, 74.0f);
}

Vec2 Scythe::getDisplayOffset()
{
	return Vec2(32.0f, -18.0f);
}

Recipe* Scythe::getRecipe()
{
	return ScythePlans::create();
}
