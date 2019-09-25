#include "Hex1.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Hex1.h"

using namespace cocos2d;

const std::string Hex1::SaveKeyHex1 = "hex-1";

Hex1* Hex1::create()
{
	Hex1* instance = new Hex1();

	instance->autorelease();

	return instance;
}

Hex1::Hex1() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Hex1::~Hex1()
{
}

Item* Hex1::clone()
{
	return Hex1::create();
}

std::string Hex1::getItemName()
{
	return Hex1::SaveKeyHex1;
}

LocalizedString* Hex1::getString()
{
	return Strings::Hexus_Cards_Hex1::create();
}

std::string Hex1::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex1::getSerializationKey()
{
	return Hex1::SaveKeyHex1;
}
