#include "Binary2.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary2::SaveKey = "binary-2";

Binary2* Binary2::create()
{
	Binary2* instance = new Binary2();

	instance->autorelease();

	return instance;
}

Binary2::Binary2() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 3 }}), ItemMeta(3, 3))
{
}

Binary2::~Binary2()
{
}

Item* Binary2::clone()
{
	return Binary2::create();
}

const std::string& Binary2::getItemName()
{
	return Binary2::SaveKey;
}

LocalizedString* Binary2::getString()
{
	return Strings::Hexus_Cards_Binary2::create();
}

const std::string& Binary2::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

const std::string& Binary2::getSerializationKey()
{
	return Binary2::SaveKey;
}

std::string Binary2::getCardKey()
{
	return CardKeys::Binary2;
}
