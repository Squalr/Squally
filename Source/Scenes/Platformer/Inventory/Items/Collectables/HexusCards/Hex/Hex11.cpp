#include "Hex11.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex11::SaveKey = "hex-11";

Hex11* Hex11::create()
{
	Hex11* instance = new Hex11();

	instance->autorelease();

	return instance;
}

Hex11::Hex11() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 13 }}), ItemMeta(3, 3))
{
}

Hex11::~Hex11()
{
}

Item* Hex11::clone()
{
	return Hex11::create();
}

const std::string& Hex11::getItemName()
{
	return Hex11::SaveKey;
}

LocalizedString* Hex11::getString()
{
	return Strings::Hexus_Cards_Hex11::create();
}

const std::string& Hex11::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

const std::string& Hex11::getIdentifier()
{
	return Hex11::SaveKey;
}

std::string Hex11::getCardKey()
{
	return CardKeys::Hex11;
}
