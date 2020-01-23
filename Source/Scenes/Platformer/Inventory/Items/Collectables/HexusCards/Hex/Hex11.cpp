#include "Hex11.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex11::SaveKeyHex11 = "hex-11";

Hex11* Hex11::create()
{
	Hex11* instance = new Hex11();

	instance->autorelease();

	return instance;
}

Hex11::Hex11() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Hex11::~Hex11()
{
}

Item* Hex11::clone()
{
	return Hex11::create();
}

std::string Hex11::getItemName()
{
	return Hex11::SaveKeyHex11;
}

LocalizedString* Hex11::getString()
{
	return Strings::Hexus_Cards_Hex11::create();
}

std::string Hex11::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex11::getSerializationKey()
{
	return Hex11::SaveKeyHex11;
}

std::string Hex11::getCardKey()
{
	return CardKeys::Hex11;
}
