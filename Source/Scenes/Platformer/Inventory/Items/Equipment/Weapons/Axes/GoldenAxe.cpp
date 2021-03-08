#include "GoldenAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/GoldenAxePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenAxe::SaveKey = "golden-axe";

GoldenAxe* GoldenAxe::create()
{
	GoldenAxe* instance = new GoldenAxe();

	instance->autorelease();

	return instance;
}

GoldenAxe::GoldenAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 11, 15, ItemStats(
	// Health
	4,
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

GoldenAxe::~GoldenAxe()
{
}

Item* GoldenAxe::clone()
{
	return GoldenAxe::create();
}

const std::string& GoldenAxe::getItemName()
{
	return GoldenAxe::SaveKey;
}

LocalizedString* GoldenAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_GoldenAxe::create();
}

const std::string& GoldenAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_GoldenAxe;
}

const std::string& GoldenAxe::getSerializationKey()
{
	return GoldenAxe::SaveKey;
}

Size GoldenAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 GoldenAxe::getWeaponCollisionOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}

Vec2 GoldenAxe::getDisplayOffset()
{
	return Vec2(28.0f, -4.0f);
}

Recipe* GoldenAxe::getRecipe()
{
	return GoldenAxePlans::create();
}
