#include "Binary11.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Binary11.h"

using namespace cocos2d;

const std::string Binary11::SaveKeyBinary11 = "binary-11";

Binary11* Binary11::create()
{
	Binary11* instance = new Binary11();

	instance->autorelease();

	return instance;
}

Binary11::Binary11() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Binary11::~Binary11()
{
}

Item* Binary11::clone()
{
	return Binary11::create();
}

std::string Binary11::getItemName()
{
	return Binary11::SaveKeyBinary11;
}

LocalizedString* Binary11::getString()
{
	return Strings::Hexus_Cards_Binary11::create();
}

std::string Binary11::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary11::getSerializationKey()
{
	return Binary11::SaveKeyBinary11;
}

std::string Binary11::getCardKey()
{
	return CardKeys::Binary11;
}
