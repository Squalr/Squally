#include "Decimal10.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal10::SaveKey = "decimal-10";

Decimal10* Decimal10::create()
{
	Decimal10* instance = new Decimal10();

	instance->autorelease();

	return instance;
}

Decimal10::Decimal10() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 12 }}), ItemMeta(3, 3))
{
}

Decimal10::~Decimal10()
{
}

Item* Decimal10::clone()
{
	return Decimal10::create();
}

LocalizedString* Decimal10::getString()
{
	return Strings::Hexus_Cards_Decimal10::create();
}

const std::string& Decimal10::getIconResource()
{
	return ItemResources::Collectables_Cards_CardDecimal;
}

const std::string& Decimal10::getIdentifier()
{
	return Decimal10::SaveKey;
}

std::string Decimal10::getCardKey()
{
	return CardKeys::Decimal10;
}
