#include "SpecialShr.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialShr::SaveKey = "special-shr";

SpecialShr* SpecialShr::create()
{
	SpecialShr* instance = new SpecialShr();

	instance->autorelease();

	return instance;
}

SpecialShr::SpecialShr() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), ItemMeta(3, 3))
{
}

SpecialShr::~SpecialShr()
{
}

Item* SpecialShr::clone()
{
	return SpecialShr::create();
}

const std::string& SpecialShr::getItemName()
{
	return SpecialShr::SaveKey;
}

LocalizedString* SpecialShr::getString()
{
	return Strings::Hexus_Cards_ShiftRight::create();
}

const std::string& SpecialShr::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialShr::getIdentifier()
{
	return SpecialShr::SaveKey;
}

std::string SpecialShr::getCardKey()
{
	return CardKeys::ShiftRight;
}
