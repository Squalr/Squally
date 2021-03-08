#include "Hex13.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex13::SaveKey = "hex-13";

Hex13* Hex13::create()
{
	Hex13* instance = new Hex13();

	instance->autorelease();

	return instance;
}

Hex13::Hex13() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 16 }}), ItemMeta(3, 3))
{
}

Hex13::~Hex13()
{
}

Item* Hex13::clone()
{
	return Hex13::create();
}

const std::string& Hex13::getItemName()
{
	return Hex13::SaveKey;
}

LocalizedString* Hex13::getString()
{
	return Strings::Hexus_Cards_Hex13::create();
}

const std::string& Hex13::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

const std::string& Hex13::getIdentifier()
{
	return Hex13::SaveKey;
}

std::string Hex13::getCardKey()
{
	return CardKeys::Hex13;
}
