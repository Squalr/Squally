#include "Decimal7.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal7::SaveKey = "decimal-7";

Decimal7* Decimal7::create()
{
	Decimal7* instance = new Decimal7();

	instance->autorelease();

	return instance;
}

Decimal7::Decimal7() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 9 }}), ItemMeta(3, 3))
{
}

Decimal7::~Decimal7()
{
}

Item* Decimal7::clone()
{
	return Decimal7::create();
}

std::string Decimal7::getItemName()
{
	return Decimal7::SaveKey;
}

LocalizedString* Decimal7::getString()
{
	return Strings::Hexus_Cards_Decimal7::create();
}

std::string Decimal7::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

std::string Decimal7::getSerializationKey()
{
	return Decimal7::SaveKey;
}

std::string Decimal7::getCardKey()
{
	return CardKeys::Decimal7;
}
