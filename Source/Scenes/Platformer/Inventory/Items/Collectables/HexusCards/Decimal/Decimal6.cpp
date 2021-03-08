#include "Decimal6.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal6::SaveKey = "decimal-6";

Decimal6* Decimal6::create()
{
	Decimal6* instance = new Decimal6();

	instance->autorelease();

	return instance;
}

Decimal6::Decimal6() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 8 }}), ItemMeta(3, 3))
{
}

Decimal6::~Decimal6()
{
}

Item* Decimal6::clone()
{
	return Decimal6::create();
}

LocalizedString* Decimal6::getString()
{
	return Strings::Hexus_Cards_Decimal6::create();
}

const std::string& Decimal6::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

const std::string& Decimal6::getIdentifier()
{
	return Decimal6::SaveKey;
}

std::string Decimal6::getCardKey()
{
	return CardKeys::Decimal6;
}
