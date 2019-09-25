#include "Hex13.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Hex13.h"

using namespace cocos2d;

const std::string Hex13::SaveKeyHex13 = "hex-13";

Hex13* Hex13::create()
{
	Hex13* instance = new Hex13();

	instance->autorelease();

	return instance;
}

Hex13::Hex13() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Hex13::~Hex13()
{
}

Item* Hex13::clone()
{
	return Hex13::create();
}

std::string Hex13::getItemName()
{
	return Hex13::SaveKeyHex13;
}

LocalizedString* Hex13::getString()
{
	return Strings::Hexus_Cards_Hex13::create();
}

std::string Hex13::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex13::getSerializationKey()
{
	return Hex13::SaveKeyHex13;
}
