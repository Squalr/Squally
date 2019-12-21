#include "Decimal4.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal4::SaveKeyDecimal4 = "decimal-4";

Decimal4* Decimal4::create()
{
	Decimal4* instance = new Decimal4();

	instance->autorelease();

	return instance;
}

Decimal4::Decimal4() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3))
{
}

Decimal4::~Decimal4()
{
}

Item* Decimal4::clone()
{
	return Decimal4::create();
}

std::string Decimal4::getItemName()
{
	return Decimal4::SaveKeyDecimal4;
}

LocalizedString* Decimal4::getString()
{
	return Strings::Hexus_Cards_Decimal4::create();
}

std::string Decimal4::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal4::getSerializationKey()
{
	return Decimal4::SaveKeyDecimal4;
}

std::string Decimal4::getCardKey()
{
	return CardKeys::Decimal4;
}
