#include "Binary15.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Binary15::SaveKeyBinary15 = "binary-15";

Binary15* Binary15::create()
{
	Binary15* instance = new Binary15();

	instance->autorelease();

	return instance;
}

Binary15::Binary15() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3))
{
}

Binary15::~Binary15()
{
}

Item* Binary15::clone()
{
	return Binary15::create();
}

std::string Binary15::getItemName()
{
	return Binary15::SaveKeyBinary15;
}

LocalizedString* Binary15::getString()
{
	return Strings::Hexus_Cards_Binary15::create();
}

std::string Binary15::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary15::getSerializationKey()
{
	return Binary15::SaveKeyBinary15;
}

std::string Binary15::getCardKey()
{
	return CardKeys::Binary15;
}
