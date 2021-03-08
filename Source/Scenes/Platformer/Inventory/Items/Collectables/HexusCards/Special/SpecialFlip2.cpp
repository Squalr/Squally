#include "SpecialFlip2.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialFlip2::SaveKey = "special-flip2";

SpecialFlip2* SpecialFlip2::create()
{
	SpecialFlip2* instance = new SpecialFlip2();

	instance->autorelease();

	return instance;
}

SpecialFlip2::SpecialFlip2() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 4 }}), ItemMeta(3, 3))
{
}

SpecialFlip2::~SpecialFlip2()
{
}

Item* SpecialFlip2::clone()
{
	return SpecialFlip2::create();
}

const std::string& SpecialFlip2::getItemName()
{
	return SpecialFlip2::SaveKey;
}

LocalizedString* SpecialFlip2::getString()
{
	return Strings::Hexus_Cards_Flip2::create();
}

const std::string& SpecialFlip2::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialFlip2::getIdentifier()
{
	return SpecialFlip2::SaveKey;
}

std::string SpecialFlip2::getCardKey()
{
	return CardKeys::Flip2;
}
