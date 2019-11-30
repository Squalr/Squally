#include "Rend.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Rend::SaveKeyRend = "rend";

Rend* Rend::create()
{
	Rend* instance = new Rend();

	instance->autorelease();

	return instance;
}

Rend::Rend() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 4, 7)
{
}

Rend::~Rend()
{
}

Item* Rend::clone()
{
	return Rend::create();
}

std::string Rend::getItemName()
{
	return Rend::SaveKeyRend;
}

LocalizedString* Rend::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_Rend::create();
}

std::string Rend::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_Rend;
}

std::string Rend::getSerializationKey()
{
	return Rend::SaveKeyRend;
}

Size Rend::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 Rend::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
