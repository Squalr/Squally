#include "Decimal2.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal2::SaveKeyDecimal2 = "decimal-2";

Decimal2* Decimal2::create()
{
	Decimal2* instance = new Decimal2();

	instance->autorelease();

	return instance;
}

Decimal2::Decimal2() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3))
{
}

Decimal2::~Decimal2()
{
}

Item* Decimal2::clone()
{
	return Decimal2::create();
}

std::string Decimal2::getItemName()
{
	return Decimal2::SaveKeyDecimal2;
}

LocalizedString* Decimal2::getString()
{
	return Strings::Hexus_Cards_Decimal2::create();
}

std::string Decimal2::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal2::getSerializationKey()
{
	return Decimal2::SaveKeyDecimal2;
}

std::string Decimal2::getCardKey()
{
	return CardKeys::Decimal2;
}
