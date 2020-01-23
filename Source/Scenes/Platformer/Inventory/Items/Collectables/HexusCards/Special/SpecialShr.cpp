#include "SpecialShr.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialShr::SaveKeySpecialShr = "special-shr";

SpecialShr* SpecialShr::create()
{
	SpecialShr* instance = new SpecialShr();

	instance->autorelease();

	return instance;
}

SpecialShr::SpecialShr() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}), ItemMeta(3, 3))
{
}

SpecialShr::~SpecialShr()
{
}

Item* SpecialShr::clone()
{
	return SpecialShr::create();
}

std::string SpecialShr::getItemName()
{
	return SpecialShr::SaveKeySpecialShr;
}

LocalizedString* SpecialShr::getString()
{
	return Strings::Hexus_Cards_ShiftRight::create();
}

std::string SpecialShr::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialShr::getSerializationKey()
{
	return SpecialShr::SaveKeySpecialShr;
}

std::string SpecialShr::getCardKey()
{
	return CardKeys::ShiftRight;
}
