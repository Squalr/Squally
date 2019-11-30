#include "Decimal3.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal3::SaveKeyDecimal3 = "decimal-3";

Decimal3* Decimal3::create()
{
	Decimal3* instance = new Decimal3();

	instance->autorelease();

	return instance;
}

Decimal3::Decimal3() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Decimal3::~Decimal3()
{
}

Item* Decimal3::clone()
{
	return Decimal3::create();
}

std::string Decimal3::getItemName()
{
	return Decimal3::SaveKeyDecimal3;
}

LocalizedString* Decimal3::getString()
{
	return Strings::Hexus_Cards_Decimal3::create();
}

std::string Decimal3::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal3::getSerializationKey()
{
	return Decimal3::SaveKeyDecimal3;
}

std::string Decimal3::getCardKey()
{
	return CardKeys::Decimal3;
}
