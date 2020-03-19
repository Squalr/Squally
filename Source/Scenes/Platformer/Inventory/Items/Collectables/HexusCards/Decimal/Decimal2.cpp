#include "Decimal2.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal2::SaveKey = "decimal-2";

Decimal2* Decimal2::create()
{
	Decimal2* instance = new Decimal2();

	instance->autorelease();

	return instance;
}

Decimal2::Decimal2() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
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
	return Decimal2::SaveKey;
}

LocalizedString* Decimal2::getString()
{
	return Strings::Hexus_Cards_Decimal2::create();
}

std::string Decimal2::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

std::string Decimal2::getSerializationKey()
{
	return Decimal2::SaveKey;
}

std::string Decimal2::getCardKey()
{
	return CardKeys::Decimal2;
}
