#include "Binary7.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary7::SaveKey = "binary-7";

Binary7* Binary7::create()
{
	Binary7* instance = new Binary7();

	instance->autorelease();

	return instance;
}

Binary7::Binary7() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 9 }}), ItemMeta(3, 3))
{
}

Binary7::~Binary7()
{
}

Item* Binary7::clone()
{
	return Binary7::create();
}

LocalizedString* Binary7::getString()
{
	return Strings::Hexus_Cards_Binary7::create();
}

const std::string& Binary7::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

const std::string& Binary7::getIdentifier()
{
	return Binary7::SaveKey;
}

std::string Binary7::getCardKey()
{
	return CardKeys::Binary7;
}
