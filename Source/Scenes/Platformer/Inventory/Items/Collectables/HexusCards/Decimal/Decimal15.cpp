#include "Decimal15.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal15::SaveKey = "decimal-15";

Decimal15* Decimal15::create()
{
	Decimal15* instance = new Decimal15();

	instance->autorelease();

	return instance;
}

Decimal15::Decimal15() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 20 }}), ItemMeta(3, 3))
{
}

Decimal15::~Decimal15()
{
}

Item* Decimal15::clone()
{
	return Decimal15::create();
}

LocalizedString* Decimal15::getString()
{
	return Strings::Hexus_Cards_Decimal15::create();
}

const std::string& Decimal15::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

const std::string& Decimal15::getIdentifier()
{
	return Decimal15::SaveKey;
}

std::string Decimal15::getCardKey()
{
	return CardKeys::Decimal15;
}
