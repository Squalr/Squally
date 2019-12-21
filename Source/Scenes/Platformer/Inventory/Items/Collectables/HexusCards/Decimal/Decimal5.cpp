#include "Decimal5.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal5::SaveKeyDecimal5 = "decimal-5";

Decimal5* Decimal5::create()
{
	Decimal5* instance = new Decimal5();

	instance->autorelease();

	return instance;
}

Decimal5::Decimal5() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3))
{
}

Decimal5::~Decimal5()
{
}

Item* Decimal5::clone()
{
	return Decimal5::create();
}

std::string Decimal5::getItemName()
{
	return Decimal5::SaveKeyDecimal5;
}

LocalizedString* Decimal5::getString()
{
	return Strings::Hexus_Cards_Decimal5::create();
}

std::string Decimal5::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal5::getSerializationKey()
{
	return Decimal5::SaveKeyDecimal5;
}

std::string Decimal5::getCardKey()
{
	return CardKeys::Decimal5;
}
