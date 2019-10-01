#include "Hex2.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Hex2.h"

using namespace cocos2d;

const std::string Hex2::SaveKeyHex2 = "hex-2";

Hex2* Hex2::create()
{
	Hex2* instance = new Hex2();

	instance->autorelease();

	return instance;
}

Hex2::Hex2() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Hex2::~Hex2()
{
}

Item* Hex2::clone()
{
	return Hex2::create();
}

std::string Hex2::getItemName()
{
	return Hex2::SaveKeyHex2;
}

LocalizedString* Hex2::getString()
{
	return Strings::Hexus_Cards_Hex2::create();
}

std::string Hex2::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex2::getSerializationKey()
{
	return Hex2::SaveKeyHex2;
}

std::string Hex2::getCardKey()
{
	return CardKeys::Hex2;
}
