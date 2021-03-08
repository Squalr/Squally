#include "Hex12.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex12::SaveKey = "hex-12";

Hex12* Hex12::create()
{
	Hex12* instance = new Hex12();

	instance->autorelease();

	return instance;
}

Hex12::Hex12() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 14 }}), ItemMeta(3, 3))
{
}

Hex12::~Hex12()
{
}

Item* Hex12::clone()
{
	return Hex12::create();
}

const std::string& Hex12::getItemName()
{
	return Hex12::SaveKey;
}

LocalizedString* Hex12::getString()
{
	return Strings::Hexus_Cards_Hex12::create();
}

const std::string& Hex12::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

const std::string& Hex12::getIdentifier()
{
	return Hex12::SaveKey;
}

std::string Hex12::getCardKey()
{
	return CardKeys::Hex12;
}
