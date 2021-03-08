#include "Decimal8.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal8::SaveKey = "decimal-8";

Decimal8* Decimal8::create()
{
	Decimal8* instance = new Decimal8();

	instance->autorelease();

	return instance;
}

Decimal8::Decimal8() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 10 }}), ItemMeta(3, 3))
{
}

Decimal8::~Decimal8()
{
}

Item* Decimal8::clone()
{
	return Decimal8::create();
}

const std::string& Decimal8::getItemName()
{
	return Decimal8::SaveKey;
}

LocalizedString* Decimal8::getString()
{
	return Strings::Hexus_Cards_Decimal8::create();
}

const std::string& Decimal8::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

const std::string& Decimal8::getIdentifier()
{
	return Decimal8::SaveKey;
}

std::string Decimal8::getCardKey()
{
	return CardKeys::Decimal8;
}
