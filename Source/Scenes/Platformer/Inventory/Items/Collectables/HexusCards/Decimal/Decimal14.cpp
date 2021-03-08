#include "Decimal14.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal14::SaveKey = "decimal-14";

Decimal14* Decimal14::create()
{
	Decimal14* instance = new Decimal14();

	instance->autorelease();

	return instance;
}

Decimal14::Decimal14() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 18 }}), ItemMeta(3, 3))
{
}

Decimal14::~Decimal14()
{
}

Item* Decimal14::clone()
{
	return Decimal14::create();
}

const std::string& Decimal14::getItemName()
{
	return Decimal14::SaveKey;
}

LocalizedString* Decimal14::getString()
{
	return Strings::Hexus_Cards_Decimal14::create();
}

const std::string& Decimal14::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

const std::string& Decimal14::getIdentifier()
{
	return Decimal14::SaveKey;
}

std::string Decimal14::getCardKey()
{
	return CardKeys::Decimal14;
}
