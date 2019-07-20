#include "WoodenShield.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Offhands/Shields/WoodenShield.h"

using namespace cocos2d;

const std::string WoodenShield::SaveKeyWoodenShield = "wooden-shield";

WoodenShield* WoodenShield::create()
{
	WoodenShield* instance = new WoodenShield();

	instance->autorelease();

	return instance;
}

WoodenShield::WoodenShield() : super(3, 6)
{
}

WoodenShield::~WoodenShield()
{
}

Item* WoodenShield::clone()
{
	return WoodenShield::create();
}

std::string WoodenShield::getItemName()
{
	return WoodenShield::SaveKeyWoodenShield;
}

LocalizedString* WoodenShield::getString()
{
	return Strings::Items_Equipment_Offhands_Shields_WoodenShield::create();
}

std::string WoodenShield::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_Rend;
}

std::string WoodenShield::getSerializationKey()
{
	return WoodenShield::SaveKeyWoodenShield;
}
