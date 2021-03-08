#include "Binary14.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary14::SaveKey = "binary-14";

Binary14* Binary14::create()
{
	Binary14* instance = new Binary14();

	instance->autorelease();

	return instance;
}

Binary14::Binary14() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 18 }}), ItemMeta(3, 3))
{
}

Binary14::~Binary14()
{
}

Item* Binary14::clone()
{
	return Binary14::create();
}

const std::string& Binary14::getItemName()
{
	return Binary14::SaveKey;
}

LocalizedString* Binary14::getString()
{
	return Strings::Hexus_Cards_Binary14::create();
}

const std::string& Binary14::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

const std::string& Binary14::getSerializationKey()
{
	return Binary14::SaveKey;
}

std::string Binary14::getCardKey()
{
	return CardKeys::Binary14;
}
