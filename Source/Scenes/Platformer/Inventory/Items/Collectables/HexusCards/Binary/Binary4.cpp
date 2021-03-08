#include "Binary4.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary4::SaveKey = "binary-4";

Binary4* Binary4::create()
{
	Binary4* instance = new Binary4();

	instance->autorelease();

	return instance;
}

Binary4::Binary4() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), ItemMeta(3, 3))
{
}

Binary4::~Binary4()
{
}

Item* Binary4::clone()
{
	return Binary4::create();
}

const std::string& Binary4::getItemName()
{
	return Binary4::SaveKey;
}

LocalizedString* Binary4::getString()
{
	return Strings::Hexus_Cards_Binary4::create();
}

const std::string& Binary4::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

const std::string& Binary4::getIdentifier()
{
	return Binary4::SaveKey;
}

std::string Binary4::getCardKey()
{
	return CardKeys::Binary4;
}
