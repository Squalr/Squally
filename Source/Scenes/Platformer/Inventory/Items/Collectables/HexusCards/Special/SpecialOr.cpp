#include "SpecialOr.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialOr::SaveKeySpecialOr = "special-or";

SpecialOr* SpecialOr::create()
{
	SpecialOr* instance = new SpecialOr();

	instance->autorelease();

	return instance;
}

SpecialOr::SpecialOr() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}), ItemMeta(3))
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
	return SpecialOr::SaveKeySpecialOr;
}

LocalizedString* SpecialOr::getString()
{
	return Strings::Hexus_Cards_LogicalOr::create();
}

std::string SpecialOr::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialOr::getSerializationKey()
{
	return SpecialOr::SaveKeySpecialOr;
}

std::string SpecialOr::getCardKey()
{
	return CardKeys::LogicalOr;
}
