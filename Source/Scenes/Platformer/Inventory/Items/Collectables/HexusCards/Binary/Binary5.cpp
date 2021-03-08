#include "Binary5.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary5::SaveKey = "binary-5";

Binary5* Binary5::create()
{
	Binary5* instance = new Binary5();

	instance->autorelease();

	return instance;
}

Binary5::Binary5() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 6 }}), ItemMeta(3, 3))
{
}

Binary5::~Binary5()
{
}

Item* Binary5::clone()
{
	return Binary5::create();
}

const std::string& Binary5::getItemName()
{
	return Binary5::SaveKey;
}

LocalizedString* Binary5::getString()
{
	return Strings::Hexus_Cards_Binary5::create();
}

const std::string& Binary5::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

const std::string& Binary5::getIdentifier()
{
	return Binary5::SaveKey;
}

std::string Binary5::getCardKey()
{
	return CardKeys::Binary5;
}
