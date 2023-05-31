#include "SpecialBonusMoves.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialBonusMoves::SaveKey = "special-bonus-moves";

SpecialBonusMoves* SpecialBonusMoves::create()
{
	SpecialBonusMoves* instance = new SpecialBonusMoves();

	instance->autorelease();

	return instance;
}

SpecialBonusMoves::SpecialBonusMoves() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 11 }}), ItemMeta(3, 3))
{
}

SpecialBonusMoves::~SpecialBonusMoves()
{
}

Item* SpecialBonusMoves::clone()
{
	return SpecialBonusMoves::create();
}

LocalizedString* SpecialBonusMoves::getString()
{
	return Strings::Hexus_Cards_BonusMoves::create();
}

const std::string& SpecialBonusMoves::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialBonusMoves::getIdentifier()
{
	return SpecialBonusMoves::SaveKey;
}

std::string SpecialBonusMoves::getCardKey()
{
	return CardKeys::BonusMoves;
}
