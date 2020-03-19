#include "SpecialFlip4.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialFlip4::SaveKey = "special-flip4";

SpecialFlip4* SpecialFlip4::create()
{
	SpecialFlip4* instance = new SpecialFlip4();

	instance->autorelease();

	return instance;
}

SpecialFlip4::SpecialFlip4() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 16 }}), ItemMeta(3, 3))
{
}

SpecialFlip4::~SpecialFlip4()
{
}

Item* SpecialFlip4::clone()
{
	return SpecialFlip4::create();
}

std::string SpecialFlip4::getItemName()
{
	return SpecialFlip4::SaveKey;
}

LocalizedString* SpecialFlip4::getString()
{
	return Strings::Hexus_Cards_Flip4::create();
}

std::string SpecialFlip4::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

std::string SpecialFlip4::getSerializationKey()
{
	return SpecialFlip4::SaveKey;
}

std::string SpecialFlip4::getCardKey()
{
	return CardKeys::Flip4;
}
