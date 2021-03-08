#include "Binary11.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary11::SaveKey = "binary-11";

Binary11* Binary11::create()
{
	Binary11* instance = new Binary11();

	instance->autorelease();

	return instance;
}

Binary11::Binary11() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 13 }}), ItemMeta(3, 3))
{
}

Binary11::~Binary11()
{
}

Item* Binary11::clone()
{
	return Binary11::create();
}

const std::string& Binary11::getItemName()
{
	return Binary11::SaveKey;
}

LocalizedString* Binary11::getString()
{
	return Strings::Hexus_Cards_Binary11::create();
}

const std::string& Binary11::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

const std::string& Binary11::getIdentifier()
{
	return Binary11::SaveKey;
}

std::string Binary11::getCardKey()
{
	return CardKeys::Binary11;
}
