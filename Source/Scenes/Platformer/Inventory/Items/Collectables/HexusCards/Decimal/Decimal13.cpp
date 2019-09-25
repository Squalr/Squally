#include "Decimal13.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Decimal13.h"

using namespace cocos2d;

const std::string Decimal13::SaveKeyDecimal13 = "decimal-13";

Decimal13* Decimal13::create()
{
	Decimal13* instance = new Decimal13();

	instance->autorelease();

	return instance;
}

Decimal13::Decimal13() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Decimal13::~Decimal13()
{
}

Item* Decimal13::clone()
{
	return Decimal13::create();
}

std::string Decimal13::getItemName()
{
	return Decimal13::SaveKeyDecimal13;
}

LocalizedString* Decimal13::getString()
{
	return Strings::Hexus_Cards_Decimal13::create();
}

std::string Decimal13::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal13::getSerializationKey()
{
	return Decimal13::SaveKeyDecimal13;
}
