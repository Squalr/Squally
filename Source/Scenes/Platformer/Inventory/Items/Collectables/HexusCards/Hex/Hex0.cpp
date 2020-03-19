#include "Hex0.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex0::SaveKey = "hex-0";

Hex0* Hex0::create()
{
	Hex0* instance = new Hex0();

	instance->autorelease();

	return instance;
}

Hex0::Hex0() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Hex0::~Hex0()
{
}

Item* Hex0::clone()
{
	return Hex0::create();
}

std::string Hex0::getItemName()
{
	return Hex0::SaveKey;
}

LocalizedString* Hex0::getString()
{
	return Strings::Hexus_Cards_Hex0::create();
}

std::string Hex0::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

std::string Hex0::getSerializationKey()
{
	return Hex0::SaveKey;
}

std::string Hex0::getCardKey()
{
	return CardKeys::Hex0;
}
