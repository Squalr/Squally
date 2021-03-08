#include "Binary15.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary15::SaveKey = "binary-15";

Binary15* Binary15::create()
{
	Binary15* instance = new Binary15();

	instance->autorelease();

	return instance;
}

Binary15::Binary15() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 20 }}), ItemMeta(3, 3))
{
}

Binary15::~Binary15()
{
}

Item* Binary15::clone()
{
	return Binary15::create();
}

const std::string& Binary15::getItemName()
{
	return Binary15::SaveKey;
}

LocalizedString* Binary15::getString()
{
	return Strings::Hexus_Cards_Binary15::create();
}

const std::string& Binary15::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

const std::string& Binary15::getIdentifier()
{
	return Binary15::SaveKey;
}

std::string Binary15::getCardKey()
{
	return CardKeys::Binary15;
}
