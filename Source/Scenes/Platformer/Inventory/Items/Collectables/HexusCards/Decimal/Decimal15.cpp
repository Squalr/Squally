#include "Decimal15.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal15::SaveKeyDecimal15 = "decimal-15";

Decimal15* Decimal15::create()
{
	Decimal15* instance = new Decimal15();

	instance->autorelease();

	return instance;
}

Decimal15::Decimal15() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Decimal15::~Decimal15()
{
}

Item* Decimal15::clone()
{
	return Decimal15::create();
}

std::string Decimal15::getItemName()
{
	return Decimal15::SaveKeyDecimal15;
}

LocalizedString* Decimal15::getString()
{
	return Strings::Hexus_Cards_Decimal15::create();
}

std::string Decimal15::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

std::string Decimal15::getSerializationKey()
{
	return Decimal15::SaveKeyDecimal15;
}

std::string Decimal15::getCardKey()
{
	return CardKeys::Decimal15;
}
