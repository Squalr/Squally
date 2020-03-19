#include "Binary9.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary9::SaveKey = "binary-9";

Binary9* Binary9::create()
{
	Binary9* instance = new Binary9();

	instance->autorelease();

	return instance;
}

Binary9::Binary9() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 11 }}), ItemMeta(3, 3))
{
}

Binary9::~Binary9()
{
}

Item* Binary9::clone()
{
	return Binary9::create();
}

std::string Binary9::getItemName()
{
	return Binary9::SaveKey;
}

LocalizedString* Binary9::getString()
{
	return Strings::Hexus_Cards_Binary9::create();
}

std::string Binary9::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

std::string Binary9::getSerializationKey()
{
	return Binary9::SaveKey;
}

std::string Binary9::getCardKey()
{
	return CardKeys::Binary9;
}
