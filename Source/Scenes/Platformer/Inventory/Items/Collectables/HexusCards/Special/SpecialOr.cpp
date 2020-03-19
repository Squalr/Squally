#include "SpecialOr.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialOr::SaveKey = "special-or";

SpecialOr* SpecialOr::create()
{
	SpecialOr* instance = new SpecialOr();

	instance->autorelease();

	return instance;
}

SpecialOr::SpecialOr() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 7 }}), ItemMeta(3, 3))
{
}

SpecialOr::~SpecialOr()
{
}

Item* SpecialOr::clone()
{
	return SpecialOr::create();
}

std::string SpecialOr::getItemName()
{
	return SpecialOr::SaveKey;
}

LocalizedString* SpecialOr::getString()
{
	return Strings::Hexus_Cards_LogicalOr::create();
}

std::string SpecialOr::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

std::string SpecialOr::getSerializationKey()
{
	return SpecialOr::SaveKey;
}

std::string SpecialOr::getCardKey()
{
	return CardKeys::LogicalOr;
}
