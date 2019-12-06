#include "Decimal14.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal14::SaveKeyDecimal14 = "decimal-14";

Decimal14* Decimal14::create()
{
	Decimal14* instance = new Decimal14();

	instance->autorelease();

	return instance;
}

Decimal14::Decimal14() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3))
{
}

Decimal14::~Decimal14()
{
}

Item* Decimal14::clone()
{
	return Decimal14::create();
}

std::string Decimal14::getItemName()
{
	return Decimal14::SaveKeyDecimal14;
}

LocalizedString* Decimal14::getString()
{
	return Strings::Hexus_Cards_Decimal14::create();
}

std::string Decimal14::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal14::getSerializationKey()
{
	return Decimal14::SaveKeyDecimal14;
}

std::string Decimal14::getCardKey()
{
	return CardKeys::Decimal14;
}
