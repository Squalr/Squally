#include "Decimal0.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal0::SaveKeyDecimal0 = "decimal-0";

Decimal0* Decimal0::create()
{
	Decimal0* instance = new Decimal0();

	instance->autorelease();

	return instance;
}

Decimal0::Decimal0() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Decimal0::~Decimal0()
{
}

Item* Decimal0::clone()
{
	return Decimal0::create();
}

std::string Decimal0::getItemName()
{
	return Decimal0::SaveKeyDecimal0;
}

LocalizedString* Decimal0::getString()
{
	return Strings::Hexus_Cards_Decimal0::create();
}

std::string Decimal0::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal0::getSerializationKey()
{
	return Decimal0::SaveKeyDecimal0;
}

std::string Decimal0::getCardKey()
{
	return CardKeys::Decimal0;
}
