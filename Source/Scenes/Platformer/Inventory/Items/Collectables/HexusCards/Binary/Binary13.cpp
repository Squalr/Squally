#include "Binary13.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary13::SaveKeyBinary13 = "binary-13";

Binary13* Binary13::create()
{
	Binary13* instance = new Binary13();

	instance->autorelease();

	return instance;
}

Binary13::Binary13() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Binary13::~Binary13()
{
}

Item* Binary13::clone()
{
	return Binary13::create();
}

std::string Binary13::getItemName()
{
	return Binary13::SaveKeyBinary13;
}

LocalizedString* Binary13::getString()
{
	return Strings::Hexus_Cards_Binary13::create();
}

std::string Binary13::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary13::getSerializationKey()
{
	return Binary13::SaveKeyBinary13;
}

std::string Binary13::getCardKey()
{
	return CardKeys::Binary13;
}
