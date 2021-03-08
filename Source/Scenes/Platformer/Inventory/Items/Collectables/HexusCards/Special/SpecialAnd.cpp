#include "SpecialAnd.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialAnd::SaveKey = "special-and";

SpecialAnd* SpecialAnd::create()
{
	SpecialAnd* instance = new SpecialAnd();

	instance->autorelease();

	return instance;
}

SpecialAnd::SpecialAnd() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 7 }}), ItemMeta(3, 3))
{
}

SpecialAnd::~SpecialAnd()
{
}

Item* SpecialAnd::clone()
{
	return SpecialAnd::create();
}

LocalizedString* SpecialAnd::getString()
{
	return Strings::Hexus_Cards_LogicalAnd::create();
}

const std::string& SpecialAnd::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialAnd::getIdentifier()
{
	return SpecialAnd::SaveKey;
}

std::string SpecialAnd::getCardKey()
{
	return CardKeys::LogicalAnd;
}
