#include "Decimal13.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal13::SaveKey = "decimal-13";

Decimal13* Decimal13::create()
{
	Decimal13* instance = new Decimal13();

	instance->autorelease();

	return instance;
}

Decimal13::Decimal13() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 16 }}), ItemMeta(3, 3))
{
}

Decimal13::~Decimal13()
{
}

Item* Decimal13::clone()
{
	return Decimal13::create();
}

LocalizedString* Decimal13::getString()
{
	return Strings::Hexus_Cards_Decimal13::create();
}

const std::string& Decimal13::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

const std::string& Decimal13::getIdentifier()
{
	return Decimal13::SaveKey;
}

std::string Decimal13::getCardKey()
{
	return CardKeys::Decimal13;
}
