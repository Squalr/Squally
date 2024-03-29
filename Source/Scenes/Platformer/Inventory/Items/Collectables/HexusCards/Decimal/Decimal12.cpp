#include "Decimal12.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal12::SaveKey = "decimal-12";

Decimal12* Decimal12::create()
{
	Decimal12* instance = new Decimal12();

	instance->autorelease();

	return instance;
}

Decimal12::Decimal12() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), HexusCard::TuneCost(12) }}), ItemMeta(3, 3))
{
}

Decimal12::~Decimal12()
{
}

Item* Decimal12::clone()
{
	return Decimal12::create();
}

LocalizedString* Decimal12::getString()
{
	return Strings::Hexus_Cards_Decimal12::create();
}

const std::string& Decimal12::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

const std::string& Decimal12::getIdentifier()
{
	return Decimal12::SaveKey;
}

std::string Decimal12::getCardKey()
{
	return CardKeys::Decimal12;
}
