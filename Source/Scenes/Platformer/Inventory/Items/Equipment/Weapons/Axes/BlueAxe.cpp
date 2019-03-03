#include "BlueAxe.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Axes/BlueAxe.h"

using namespace cocos2d;

const std::string BlueAxe::SaveKeyBlueAxe = "blue-axe";

BlueAxe* BlueAxe::create()
{
	BlueAxe* instance = new BlueAxe();

	instance->autorelease();

	return instance;
}

BlueAxe::BlueAxe() : super(4, 7)
{
}

BlueAxe::~BlueAxe()
{
}

Item* BlueAxe::clone()
{
	return BlueAxe::create();
}

LocalizedString* BlueAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_BlueAxe::create();
}

std::string BlueAxe::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_BlueAxe;
}

std::string BlueAxe::getSerializationKey()
{
	return BlueAxe::SaveKeyBlueAxe;
}
