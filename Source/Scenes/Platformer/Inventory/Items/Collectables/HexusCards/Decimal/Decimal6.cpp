#include "Decimal6.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal6::SaveKeyDecimal6 = "decimal-6";

Decimal6* Decimal6::create()
{
	Decimal6* instance = new Decimal6();

	instance->autorelease();

	return instance;
}

Decimal6::Decimal6() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3))
{
}

Decimal6::~Decimal6()
{
}

Item* Decimal6::clone()
{
	return Decimal6::create();
}

std::string Decimal6::getItemName()
{
	return Decimal6::SaveKeyDecimal6;
}

LocalizedString* Decimal6::getString()
{
	return Strings::Hexus_Cards_Decimal6::create();
}

std::string Decimal6::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal6::getSerializationKey()
{
	return Decimal6::SaveKeyDecimal6;
}

std::string Decimal6::getCardKey()
{
	return CardKeys::Decimal6;
}
