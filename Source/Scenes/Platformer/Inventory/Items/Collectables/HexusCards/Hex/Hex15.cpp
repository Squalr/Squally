#include "Hex15.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex15::SaveKey = "hex-15";

Hex15* Hex15::create()
{
	Hex15* instance = new Hex15();

	instance->autorelease();

	return instance;
}

Hex15::Hex15() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 20 }}), ItemMeta(3, 3))
{
}

Hex15::~Hex15()
{
}

Item* Hex15::clone()
{
	return Hex15::create();
}

const std::string& Hex15::getItemName()
{
	return Hex15::SaveKey;
}

LocalizedString* Hex15::getString()
{
	return Strings::Hexus_Cards_Hex15::create();
}

const std::string& Hex15::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

const std::string& Hex15::getSerializationKey()
{
	return Hex15::SaveKey;
}

std::string Hex15::getCardKey()
{
	return CardKeys::Hex15;
}
