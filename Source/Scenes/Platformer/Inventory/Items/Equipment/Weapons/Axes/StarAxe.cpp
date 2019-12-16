#include "StarAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string StarAxe::SaveKeyStarAxe = "star-axe";

StarAxe* StarAxe::create()
{
	StarAxe* instance = new StarAxe();

	instance->autorelease();

	return instance;
}

StarAxe::StarAxe() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 4, 7, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

StarAxe::~StarAxe()
{
}

Item* StarAxe::clone()
{
	return StarAxe::create();
}

std::string StarAxe::getItemName()
{
	return StarAxe::SaveKeyStarAxe;
}

LocalizedString* StarAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_StarAxe::create();
}

std::string StarAxe::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_StarAxe;
}

std::string StarAxe::getSerializationKey()
{
	return StarAxe::SaveKeyStarAxe;
}

Size StarAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 StarAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
