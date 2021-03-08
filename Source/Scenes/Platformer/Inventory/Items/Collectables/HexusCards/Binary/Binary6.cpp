#include "Binary6.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary6::SaveKey = "binary-6";

Binary6* Binary6::create()
{
	Binary6* instance = new Binary6();

	instance->autorelease();

	return instance;
}

Binary6::Binary6() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 8 }}), ItemMeta(3, 3))
{
}

Binary6::~Binary6()
{
}

Item* Binary6::clone()
{
	return Binary6::create();
}

const std::string& Binary6::getItemName()
{
	return Binary6::SaveKey;
}

LocalizedString* Binary6::getString()
{
	return Strings::Hexus_Cards_Binary6::create();
}

const std::string& Binary6::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

const std::string& Binary6::getIdentifier()
{
	return Binary6::SaveKey;
}

std::string Binary6::getCardKey()
{
	return CardKeys::Binary6;
}
