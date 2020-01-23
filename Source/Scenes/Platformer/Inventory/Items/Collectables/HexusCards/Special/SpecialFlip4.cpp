#include "SpecialFlip4.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialFlip4::SaveKeySpecialFlip4 = "special-flip4";

SpecialFlip4* SpecialFlip4::create()
{
	SpecialFlip4* instance = new SpecialFlip4();

	instance->autorelease();

	return instance;
}

SpecialFlip4::SpecialFlip4() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}), ItemMeta(3, 3))
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
	return SpecialFlip4::SaveKeySpecialFlip4;
}

LocalizedString* SpecialFlip4::getString()
{
	return Strings::Hexus_Cards_Flip4::create();
}

std::string SpecialFlip4::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialFlip4::getSerializationKey()
{
	return SpecialFlip4::SaveKeySpecialFlip4;
}

std::string SpecialFlip4::getCardKey()
{
	return CardKeys::Flip4;
}
