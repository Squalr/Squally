#include "Binary7.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary7::SaveKeyBinary7 = "binary-7";

Binary7* Binary7::create()
{
	Binary7* instance = new Binary7();

	instance->autorelease();

	return instance;
}

Binary7::Binary7() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Binary7::~Binary7()
{
}

Item* Binary7::clone()
{
	return Binary7::create();
}

std::string Binary7::getItemName()
{
	return Binary7::SaveKeyBinary7;
}

LocalizedString* Binary7::getString()
{
	return Strings::Hexus_Cards_Binary7::create();
}

std::string Binary7::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

std::string Binary7::getSerializationKey()
{
	return Binary7::SaveKeyBinary7;
}

std::string Binary7::getCardKey()
{
	return CardKeys::Binary7;
}
