#include "Binary10.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary10::SaveKeyBinary10 = "binary-10";

Binary10* Binary10::create()
{
	Binary10* instance = new Binary10();

	instance->autorelease();

	return instance;
}

Binary10::Binary10() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Binary10::~Binary10()
{
}

Item* Binary10::clone()
{
	return Binary10::create();
}

std::string Binary10::getItemName()
{
	return Binary10::SaveKeyBinary10;
}

LocalizedString* Binary10::getString()
{
	return Strings::Hexus_Cards_Binary10::create();
}

std::string Binary10::getIconResource()
{
	return ItemResources::Collectables_Cards_CardBinary;
}

std::string Binary10::getSerializationKey()
{
	return Binary10::SaveKeyBinary10;
}

std::string Binary10::getCardKey()
{
	return CardKeys::Binary10;
}
