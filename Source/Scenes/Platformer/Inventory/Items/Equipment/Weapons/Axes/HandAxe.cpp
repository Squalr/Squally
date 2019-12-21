#include "HandAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HandAxe::SaveKeyHandAxe = "hand-axe";

HandAxe* HandAxe::create()
{
	HandAxe* instance = new HandAxe();

	instance->autorelease();

	return instance;
}

HandAxe::HandAxe() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 4, 7, ItemStats(
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

HandAxe::~HandAxe()
{
}

Item* HandAxe::clone()
{
	return HandAxe::create();
}

std::string HandAxe::getItemName()
{
	return HandAxe::SaveKeyHandAxe;
}

LocalizedString* HandAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_HandAxe::create();
}

std::string HandAxe::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_HandAxe;
}

std::string HandAxe::getSerializationKey()
{
	return HandAxe::SaveKeyHandAxe;
}

Size HandAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 HandAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
