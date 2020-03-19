#include "Decimal9.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal9::SaveKey = "decimal-9";

Decimal9* Decimal9::create()
{
	Decimal9* instance = new Decimal9();

	instance->autorelease();

	return instance;
}

Decimal9::Decimal9() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Decimal9::~Decimal9()
{
}

Item* Decimal9::clone()
{
	return Decimal9::create();
}

std::string Decimal9::getItemName()
{
	return Decimal9::SaveKey;
}

LocalizedString* Decimal9::getString()
{
	return Strings::Hexus_Cards_Decimal9::create();
}

std::string Decimal9::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

std::string Decimal9::getSerializationKey()
{
	return Decimal9::SaveKey;
}

std::string Decimal9::getCardKey()
{
	return CardKeys::Decimal9;
}
