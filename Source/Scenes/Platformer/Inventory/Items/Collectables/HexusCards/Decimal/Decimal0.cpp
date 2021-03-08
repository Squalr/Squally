#include "Decimal0.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal0::SaveKey = "decimal-0";

Decimal0* Decimal0::create()
{
	Decimal0* instance = new Decimal0();

	instance->autorelease();

	return instance;
}

Decimal0::Decimal0() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemMeta(3, 3))
{
}

Decimal0::~Decimal0()
{
}

Item* Decimal0::clone()
{
	return Decimal0::create();
}

const std::string& Decimal0::getItemName()
{
	return Decimal0::SaveKey;
}

LocalizedString* Decimal0::getString()
{
	return Strings::Hexus_Cards_Decimal0::create();
}

const std::string& Decimal0::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

const std::string& Decimal0::getIdentifier()
{
	return Decimal0::SaveKey;
}

std::string Decimal0::getCardKey()
{
	return CardKeys::Decimal0;
}
