#include "MithrilAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

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

MithrilAxe::MithrilAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
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

std::string MithrilAxe::getItemName()
{
	return MithrilAxe::SaveKey;
}

LocalizedString* MithrilAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_MithrilAxe::create();
}

std::string MithrilAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_MithrilAxe;
}

std::string MithrilAxe::getSerializationKey()
{
	return MithrilAxe::SaveKey;
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
