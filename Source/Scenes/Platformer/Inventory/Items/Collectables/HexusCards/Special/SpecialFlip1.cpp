#include "SpecialFlip1.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialFlip1::SaveKeySpecialFlip1 = "special-flip1";

SpecialFlip1* SpecialFlip1::create()
{
	SpecialFlip1* instance = new SpecialFlip1();

	instance->autorelease();

	return instance;
}

SpecialFlip1::SpecialFlip1() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}), ItemMeta(3))
{
}

SpecialFlip1::~SpecialFlip1()
{
}

Item* SpecialFlip1::clone()
{
	return SpecialFlip1::create();
}

std::string SpecialFlip1::getItemName()
{
	return SpecialFlip1::SaveKeySpecialFlip1;
}

LocalizedString* SpecialFlip1::getString()
{
	return Strings::Hexus_Cards_Flip1::create();
}

std::string SpecialFlip1::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialFlip1::getSerializationKey()
{
	return SpecialFlip1::SaveKeySpecialFlip1;
}

std::string SpecialFlip1::getCardKey()
{
	return CardKeys::Flip1;
}
