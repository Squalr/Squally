#include "Hex2.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex2::SaveKey = "hex-2";

Hex2* Hex2::create()
{
	Hex2* instance = new Hex2();

	instance->autorelease();

	return instance;
}

Hex2::Hex2() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
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
	return Hex2::SaveKey;
}

LocalizedString* Hex2::getString()
{
	return Strings::Hexus_Cards_Hex2::create();
}

std::string Hex2::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

std::string Hex2::getSerializationKey()
{
	return Hex2::SaveKey;
}

std::string Hex2::getCardKey()
{
	return CardKeys::Hex2;
}
