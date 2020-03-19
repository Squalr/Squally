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

SpecialAnd::SpecialAnd() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 3 }}), ItemMeta(3, 3))
{
}

SpecialAnd::~SpecialAnd()
{
}

Item* SpecialAnd::clone()
{
	return SpecialAnd::create();
}

std::string SpecialAnd::getItemName()
{
	return SpecialAnd::SaveKey;
}

LocalizedString* SpecialAnd::getString()
{
	return Strings::Hexus_Cards_LogicalAnd::create();
}

std::string SpecialAnd::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

std::string SpecialAnd::getSerializationKey()
{
	return SpecialAnd::SaveKey;
}

std::string SpecialAnd::getCardKey()
{
	return CardKeys::LogicalAnd;
}
