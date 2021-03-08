#include "Decimal4.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal4::SaveKey = "decimal-4";

Decimal4* Decimal4::create()
{
	Decimal4* instance = new Decimal4();

	instance->autorelease();

	return instance;
}

Decimal4::Decimal4() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), ItemMeta(3, 3))
{
}

Decimal4::~Decimal4()
{
}

Item* Decimal4::clone()
{
	return Decimal4::create();
}

LocalizedString* Decimal4::getString()
{
	return Strings::Hexus_Cards_Decimal4::create();
}

const std::string& Decimal4::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

const std::string& Decimal4::getIdentifier()
{
	return Decimal4::SaveKey;
}

std::string Decimal4::getCardKey()
{
	return CardKeys::Decimal4;
}
