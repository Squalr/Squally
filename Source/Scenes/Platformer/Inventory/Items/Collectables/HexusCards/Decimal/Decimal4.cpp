#include "Decimal4.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal4::SaveKeyDecimal4 = "decimal-4";

Decimal4* Decimal4::create()
{
	Decimal4* instance = new Decimal4();

	instance->autorelease();

	return instance;
}

Decimal4::Decimal4() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Decimal4::~Decimal4()
{
}

Item* Decimal4::clone()
{
	return Decimal4::create();
}

std::string Decimal4::getItemName()
{
	return Decimal4::SaveKeyDecimal4;
}

LocalizedString* Decimal4::getString()
{
	return Strings::Hexus_Cards_Decimal4::create();
}

std::string Decimal4::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

std::string Decimal4::getSerializationKey()
{
	return Decimal4::SaveKeyDecimal4;
}

std::string Decimal4::getCardKey()
{
	return CardKeys::Decimal4;
}
