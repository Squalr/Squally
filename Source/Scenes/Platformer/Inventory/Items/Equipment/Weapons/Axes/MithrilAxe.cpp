#include "MithrilAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/MithrilAxePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilAxe::SaveKey = "mithril-axe";

MithrilAxe* MithrilAxe::create()
{
	MithrilAxe* instance = new MithrilAxe();

	instance->autorelease();

	return instance;
}

MithrilAxe::MithrilAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), AXE_DAMAGE_MIN(5), AXE_DAMAGE_MAX(5), ItemStats(
	// Health
	2,
	// Mana
	3,
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

MithrilAxe::~MithrilAxe()
{
}

Item* MithrilAxe::clone()
{
	return MithrilAxe::create();
}

LocalizedString* MithrilAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_MithrilAxe::create();
}

const std::string& MithrilAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_MithrilAxe;
}

const std::string& MithrilAxe::getIdentifier()
{
	return MithrilAxe::SaveKey;
}

CSize MithrilAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return CSize(96.0f, 96.0f);
}

Vec2 MithrilAxe::getWeaponCollisionOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(-12.0f, 202.0f);
}

Vec2 MithrilAxe::getDisplayOffset()
{
	return Vec2(0.0f, -8.0f);
}

Recipe* MithrilAxe::getRecipe()
{
	return MithrilAxePlans::create();
}
