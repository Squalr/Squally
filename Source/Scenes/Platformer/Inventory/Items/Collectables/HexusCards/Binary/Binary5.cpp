#include "Binary5.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary5::SaveKeyBinary5 = "binary-5";

Binary5* Binary5::create()
{
	Binary5* instance = new Binary5();

	instance->autorelease();

	return instance;
}

Binary5::Binary5() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3))
{
}

Binary5::~Binary5()
{
}

Item* Binary5::clone()
{
	return Binary5::create();
}

std::string Binary5::getItemName()
{
	return Binary5::SaveKeyBinary5;
}

LocalizedString* Binary5::getString()
{
	return Strings::Hexus_Cards_Binary5::create();
}

std::string Binary5::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary5::getSerializationKey()
{
	return Binary5::SaveKeyBinary5;
}

std::string Binary5::getCardKey()
{
	return CardKeys::Binary5;
}
