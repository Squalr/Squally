#include "Binary3.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary3::SaveKeyBinary3 = "binary-3";

Binary3* Binary3::create()
{
	Binary3* instance = new Binary3();

	instance->autorelease();

	return instance;
}

Binary3::Binary3() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Binary3::~Binary3()
{
}

Item* Binary3::clone()
{
	return Binary3::create();
}

std::string Binary3::getItemName()
{
	return Binary3::SaveKeyBinary3;
}

LocalizedString* Binary3::getString()
{
	return Strings::Hexus_Cards_Binary3::create();
}

std::string Binary3::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary3::getSerializationKey()
{
	return Binary3::SaveKeyBinary3;
}

std::string Binary3::getCardKey()
{
	return CardKeys::Binary3;
}
