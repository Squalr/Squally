#include "Decimal10.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal10::SaveKeyDecimal10 = "decimal-10";

Decimal10* Decimal10::create()
{
	Decimal10* instance = new Decimal10();

	instance->autorelease();

	return instance;
}

Decimal10::Decimal10() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Decimal10::~Decimal10()
{
}

Item* Decimal10::clone()
{
	return Decimal10::create();
}

std::string Decimal10::getItemName()
{
	return Decimal10::SaveKeyDecimal10;
}

LocalizedString* Decimal10::getString()
{
	return Strings::Hexus_Cards_Decimal10::create();
}

std::string Decimal10::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal10::getSerializationKey()
{
	return Decimal10::SaveKeyDecimal10;
}

std::string Decimal10::getCardKey()
{
	return CardKeys::Decimal10;
}
