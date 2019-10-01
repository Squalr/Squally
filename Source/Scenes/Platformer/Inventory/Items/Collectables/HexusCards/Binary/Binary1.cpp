#include "Binary1.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Binary1.h"

using namespace cocos2d;

const std::string Binary1::SaveKeyBinary1 = "binary-1";

Binary1* Binary1::create()
{
	Binary1* instance = new Binary1();

	instance->autorelease();

	return instance;
}

Binary1::Binary1() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Binary1::~Binary1()
{
}

Item* Binary1::clone()
{
	return Binary1::create();
}

std::string Binary1::getItemName()
{
	return Binary1::SaveKeyBinary1;
}

LocalizedString* Binary1::getString()
{
	return Strings::Hexus_Cards_Binary1::create();
}

std::string Binary1::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary1::getSerializationKey()
{
	return Binary1::SaveKeyBinary1;
}

std::string Binary1::getCardKey()
{
	return CardKeys::Binary1;
}
