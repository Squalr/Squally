#include "Decimal8.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Decimal8::SaveKeyDecimal8 = "decimal-8";

Decimal8* Decimal8::create()
{
	Decimal8* instance = new Decimal8();

	instance->autorelease();

	return instance;
}

Decimal8::Decimal8() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3))
{
}

Decimal8::~Decimal8()
{
}

Item* Decimal8::clone()
{
	return Decimal8::create();
}

std::string Decimal8::getItemName()
{
	return Decimal8::SaveKeyDecimal8;
}

LocalizedString* Decimal8::getString()
{
	return Strings::Hexus_Cards_Decimal8::create();
}

std::string Decimal8::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardDecimal;
}

std::string Decimal8::getSerializationKey()
{
	return Decimal8::SaveKeyDecimal8;
}

std::string Decimal8::getCardKey()
{
	return CardKeys::Decimal8;
}
