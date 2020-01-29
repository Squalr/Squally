#include "SpecialFlip3.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialFlip3::SaveKeySpecialFlip3 = "special-flip3";

SpecialFlip3* SpecialFlip3::create()
{
	SpecialFlip3* instance = new SpecialFlip3();

	instance->autorelease();

	return instance;
}

SpecialFlip3::SpecialFlip3() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 3 }}), ItemMeta(3, 3))
{
}

SpecialFlip3::~SpecialFlip3()
{
}

Item* SpecialFlip3::clone()
{
	return SpecialFlip3::create();
}

std::string SpecialFlip3::getItemName()
{
	return SpecialFlip3::SaveKeySpecialFlip3;
}

LocalizedString* SpecialFlip3::getString()
{
	return Strings::Hexus_Cards_Flip3::create();
}

std::string SpecialFlip3::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialFlip3::getSerializationKey()
{
	return SpecialFlip3::SaveKeySpecialFlip3;
}

std::string SpecialFlip3::getCardKey()
{
	return CardKeys::Flip3;
}
