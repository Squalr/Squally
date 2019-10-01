#include "Decimal9.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Decimal9.h"

using namespace cocos2d;

const std::string Decimal9::SaveKeyDecimal9 = "decimal-9";

Decimal9* Decimal9::create()
{
	Decimal9* instance = new Decimal9();

	instance->autorelease();

	return instance;
}

Decimal9::Decimal9() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Decimal9::~Decimal9()
{
}

Item* Decimal9::clone()
{
	return Decimal9::create();
}

std::string Decimal9::getItemName()
{
	return Decimal9::SaveKeyDecimal9;
}

LocalizedString* Decimal9::getString()
{
	return Strings::Hexus_Cards_Decimal9::create();
}

std::string Decimal9::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal9::getSerializationKey()
{
	return Decimal9::SaveKeyDecimal9;
}

std::string Decimal9::getCardKey()
{
	return CardKeys::Decimal9;
}
