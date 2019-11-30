#include "Decimal11.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal11::SaveKeyDecimal11 = "decimal-11";

Decimal11* Decimal11::create()
{
	Decimal11* instance = new Decimal11();

	instance->autorelease();

	return instance;
}

Decimal11::Decimal11() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
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
	return Decimal11::SaveKeyDecimal11;
}

LocalizedString* Decimal11::getString()
{
	return Strings::Hexus_Cards_Decimal11::create();
}

std::string Decimal11::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal11::getSerializationKey()
{
	return Decimal11::SaveKeyDecimal11;
}

std::string Decimal11::getCardKey()
{
	return CardKeys::Decimal11;
}
