#include "Binary0.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary0::SaveKey = "binary-0";

Binary0* Binary0::create()
{
	Binary0* instance = new Binary0();

	instance->autorelease();

	return instance;
}

Binary0::Binary0() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Binary0::~Binary0()
{
}

Item* Binary0::clone()
{
	return Binary0::create();
}

std::string Binary0::getItemName()
{
	return Binary0::SaveKey;
}

LocalizedString* Binary0::getString()
{
	return Strings::Hexus_Cards_Binary0::create();
}

std::string Binary0::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

std::string Binary0::getSerializationKey()
{
	return Binary0::SaveKey;
}

std::string Binary0::getCardKey()
{
	return CardKeys::Binary0;
}
