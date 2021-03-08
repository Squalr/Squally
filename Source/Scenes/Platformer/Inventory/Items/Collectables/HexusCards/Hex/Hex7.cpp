#include "Hex7.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex7::SaveKey = "hex-7";

Hex7* Hex7::create()
{
	Hex7* instance = new Hex7();

	instance->autorelease();

	return instance;
}

Hex7::Hex7() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 9 }}), ItemMeta(3, 3))
{
}

Hex7::~Hex7()
{
}

Item* Hex7::clone()
{
	return Hex7::create();
}

const std::string& Hex7::getItemName()
{
	return Hex7::SaveKey;
}

LocalizedString* Hex7::getString()
{
	return Strings::Hexus_Cards_Hex7::create();
}

const std::string& Hex7::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

const std::string& Hex7::getSerializationKey()
{
	return Hex7::SaveKey;
}

std::string Hex7::getCardKey()
{
	return CardKeys::Hex7;
}
