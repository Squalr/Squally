#include "Hex1.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex1::SaveKey = "hex-1";

Hex1* Hex1::create()
{
	Hex1* instance = new Hex1();

	instance->autorelease();

	return instance;
}

Hex1::Hex1() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemMeta(3, 3))
{
}

Hex1::~Hex1()
{
}

Item* Hex1::clone()
{
	return Hex1::create();
}

const std::string& Hex1::getItemName()
{
	return Hex1::SaveKey;
}

LocalizedString* Hex1::getString()
{
	return Strings::Hexus_Cards_Hex1::create();
}

const std::string& Hex1::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

const std::string& Hex1::getSerializationKey()
{
	return Hex1::SaveKey;
}

std::string Hex1::getCardKey()
{
	return CardKeys::Hex1;
}
