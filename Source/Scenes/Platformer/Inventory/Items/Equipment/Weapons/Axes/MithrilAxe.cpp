#include "MithrilAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilAxe::SaveKeyMithrilAxe = "mithril-axe";

MithrilAxe* MithrilAxe::create()
{
	MithrilAxe* instance = new MithrilAxe();

	instance->autorelease();

	return instance;
}

MithrilAxe::MithrilAxe() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 4, 7, ItemStats(
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

MithrilAxe::~MithrilAxe()
{
}

Item* MithrilAxe::clone()
{
	return MithrilAxe::create();
}

std::string MithrilAxe::getItemName()
{
	return MithrilAxe::SaveKeyMithrilAxe;
}

LocalizedString* MithrilAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_MithrilAxe::create();
}

std::string MithrilAxe::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_MithrilAxe;
}

std::string MithrilAxe::getSerializationKey()
{
	return MithrilAxe::SaveKeyMithrilAxe;
}

Size MithrilAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 MithrilAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
