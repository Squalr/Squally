#include "Binary1.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary1::SaveKey = "binary-1";

Binary1* Binary1::create()
{
	Binary1* instance = new Binary1();

	instance->autorelease();

	return instance;
}

Binary1::Binary1() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemMeta(3, 3))
{
}

Binary1::~Binary1()
{
}

Item* Binary1::clone()
{
	return Binary1::create();
}

const std::string& Binary1::getItemName()
{
	return Binary1::SaveKey;
}

LocalizedString* Binary1::getString()
{
	return Strings::Hexus_Cards_Binary1::create();
}

const std::string& Binary1::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

const std::string& Binary1::getIdentifier()
{
	return Binary1::SaveKey;
}

std::string Binary1::getCardKey()
{
	return CardKeys::Binary1;
}
