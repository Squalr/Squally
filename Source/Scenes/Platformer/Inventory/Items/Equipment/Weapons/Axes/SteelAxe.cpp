#include "SteelAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelAxe::SaveKeySteelAxe = "steel-axe";

SteelAxe* SteelAxe::create()
{
	SteelAxe* instance = new SteelAxe();

	instance->autorelease();

	return instance;
}

SteelAxe::SteelAxe() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 4, 7)
{
}

SteelAxe::~SteelAxe()
{
}

Item* SteelAxe::clone()
{
	return SteelAxe::create();
}

std::string SteelAxe::getItemName()
{
	return SteelAxe::SaveKeySteelAxe;
}

LocalizedString* SteelAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_SteelAxe::create();
}

std::string SteelAxe::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_SteelAxe;
}

std::string SteelAxe::getSerializationKey()
{
	return SteelAxe::SaveKeySteelAxe;
}

Size SteelAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 SteelAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
