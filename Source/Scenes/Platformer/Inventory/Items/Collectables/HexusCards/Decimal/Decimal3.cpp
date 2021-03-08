#include "Decimal3.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal3::SaveKey = "decimal-3";

Decimal3* Decimal3::create()
{
	Decimal3* instance = new Decimal3();

	instance->autorelease();

	return instance;
}

Decimal3::Decimal3() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 4 }}), ItemMeta(3, 3))
{
}

Decimal3::~Decimal3()
{
}

Item* Decimal3::clone()
{
	return Decimal3::create();
}

const std::string& Decimal3::getItemName()
{
	return Decimal3::SaveKey;
}

LocalizedString* Decimal3::getString()
{
	return Strings::Hexus_Cards_Decimal3::create();
}

const std::string& Decimal3::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

const std::string& Decimal3::getIdentifier()
{
	return Decimal3::SaveKey;
}

std::string Decimal3::getCardKey()
{
	return CardKeys::Decimal3;
}
