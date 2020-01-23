#include "Decimal12.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal12::SaveKeyDecimal12 = "decimal-12";

Decimal12* Decimal12::create()
{
	Decimal12* instance = new Decimal12();

	instance->autorelease();

	return instance;
}

Decimal12::Decimal12() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Decimal12::~Decimal12()
{
}

Item* Decimal12::clone()
{
	return Decimal12::create();
}

std::string Decimal12::getItemName()
{
	return Decimal12::SaveKeyDecimal12;
}

LocalizedString* Decimal12::getString()
{
	return Strings::Hexus_Cards_Decimal12::create();
}

std::string Decimal12::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal12::getSerializationKey()
{
	return Decimal12::SaveKeyDecimal12;
}

std::string Decimal12::getCardKey()
{
	return CardKeys::Decimal12;
}
