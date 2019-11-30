#include "Binary12.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary12::SaveKeyBinary12 = "binary-12";

Binary12* Binary12::create()
{
	Binary12* instance = new Binary12();

	instance->autorelease();

	return instance;
}

Binary12::Binary12() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Binary12::~Binary12()
{
}

Item* Binary12::clone()
{
	return Binary12::create();
}

std::string Binary12::getItemName()
{
	return Binary12::SaveKeyBinary12;
}

LocalizedString* Binary12::getString()
{
	return Strings::Hexus_Cards_Binary12::create();
}

std::string Binary12::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary12::getSerializationKey()
{
	return Binary12::SaveKeyBinary12;
}

std::string Binary12::getCardKey()
{
	return CardKeys::Binary12;
}
