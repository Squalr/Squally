#include "Decimal11.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal11::SaveKey = "decimal-11";

Decimal11* Decimal11::create()
{
	Decimal11* instance = new Decimal11();

	instance->autorelease();

	return instance;
}

Decimal11::Decimal11() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Decimal11::~Decimal11()
{
}

Item* Decimal11::clone()
{
	return Decimal11::create();
}

std::string Decimal11::getItemName()
{
	return Decimal11::SaveKey;
}

LocalizedString* Decimal11::getString()
{
	return Strings::Hexus_Cards_Decimal11::create();
}

std::string Decimal11::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

std::string Decimal11::getSerializationKey()
{
	return Decimal11::SaveKey;
}

std::string Decimal11::getCardKey()
{
	return CardKeys::Decimal11;
}
