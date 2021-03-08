#include "Binary13.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary13::SaveKey = "binary-13";

Binary13* Binary13::create()
{
	Binary13* instance = new Binary13();

	instance->autorelease();

	return instance;
}

Binary13::Binary13() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 16 }}), ItemMeta(3, 3))
{
}

Binary13::~Binary13()
{
}

Item* Binary13::clone()
{
	return Binary13::create();
}

const std::string& Binary13::getItemName()
{
	return Binary13::SaveKey;
}

LocalizedString* Binary13::getString()
{
	return Strings::Hexus_Cards_Binary13::create();
}

const std::string& Binary13::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

const std::string& Binary13::getIdentifier()
{
	return Binary13::SaveKey;
}

std::string Binary13::getCardKey()
{
	return CardKeys::Binary13;
}
