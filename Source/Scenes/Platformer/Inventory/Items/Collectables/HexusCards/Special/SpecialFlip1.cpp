#include "SpecialFlip1.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialFlip1::SaveKey = "special-flip1";

SpecialFlip1* SpecialFlip1::create()
{
	SpecialFlip1* instance = new SpecialFlip1();

	instance->autorelease();

	return instance;
}

SpecialFlip1::SpecialFlip1() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

SpecialFlip1::~SpecialFlip1()
{
}

Item* SpecialFlip1::clone()
{
	return SpecialFlip1::create();
}

LocalizedString* SpecialFlip1::getString()
{
	return Strings::Hexus_Cards_Flip1::create();
}

const std::string& SpecialFlip1::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialFlip1::getIdentifier()
{
	return SpecialFlip1::SaveKey;
}

std::string SpecialFlip1::getCardKey()
{
	return CardKeys::Flip1;
}
