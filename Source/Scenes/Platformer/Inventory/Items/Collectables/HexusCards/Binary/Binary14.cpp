#include "Binary14.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary14::SaveKeyBinary14 = "binary-14";

Binary14* Binary14::create()
{
	Binary14* instance = new Binary14();

	instance->autorelease();

	return instance;
}

Binary14::Binary14() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Binary14::~Binary14()
{
}

Item* Binary14::clone()
{
	return Binary14::create();
}

std::string Binary14::getItemName()
{
	return Binary14::SaveKeyBinary14;
}

LocalizedString* Binary14::getString()
{
	return Strings::Hexus_Cards_Binary14::create();
}

std::string Binary14::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary14::getSerializationKey()
{
	return Binary14::SaveKeyBinary14;
}

std::string Binary14::getCardKey()
{
	return CardKeys::Binary14;
}
