#include "Decimal7.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Decimal7.h"

using namespace cocos2d;

const std::string Decimal7::SaveKeyDecimal7 = "decimal-7";

Decimal7* Decimal7::create()
{
	Decimal7* instance = new Decimal7();

	instance->autorelease();

	return instance;
}

Decimal7::Decimal7() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
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
	return Decimal7::SaveKeyDecimal7;
}

LocalizedString* Decimal7::getString()
{
	return Strings::Hexus_Cards_Decimal7::create();
}

std::string Decimal7::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal7::getSerializationKey()
{
	return Decimal7::SaveKeyDecimal7;
}
