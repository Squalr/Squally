#include "SpecialFlip3.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialFlip3::SaveKey = "special-flip3";

SpecialFlip3* SpecialFlip3::create()
{
	SpecialFlip3* instance = new SpecialFlip3();

	instance->autorelease();

	return instance;
}

SpecialFlip3::SpecialFlip3() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 17 }}), ItemMeta(3, 3))
{
}

SpecialFlip3::~SpecialFlip3()
{
}

Item* SpecialFlip3::clone()
{
	return SpecialFlip3::create();
}

LocalizedString* SpecialFlip3::getString()
{
	return Strings::Hexus_Cards_Flip3::create();
}

const std::string& SpecialFlip3::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialFlip3::getIdentifier()
{
	return SpecialFlip3::SaveKey;
}

std::string SpecialFlip3::getCardKey()
{
	return CardKeys::Flip3;
}
