#include "SpecialShrCircular.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialShrCircular::SaveKey = "special-shr-circular";

SpecialShrCircular* SpecialShrCircular::create()
{
	SpecialShrCircular* instance = new SpecialShrCircular();

	instance->autorelease();

	return instance;
}

SpecialShrCircular::SpecialShrCircular() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 7 }}), ItemMeta(3, 3))
{
}

SpecialShrCircular::~SpecialShrCircular()
{
}

Item* SpecialShrCircular::clone()
{
	return SpecialShrCircular::create();
}

const std::string& SpecialShrCircular::getItemName()
{
	return SpecialShrCircular::SaveKey;
}

LocalizedString* SpecialShrCircular::getString()
{
	return Strings::Hexus_Cards_ShiftRightCircular::create();
}

const std::string& SpecialShrCircular::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialShrCircular::getIdentifier()
{
	return SpecialShrCircular::SaveKey;
}

std::string SpecialShrCircular::getCardKey()
{
	return CardKeys::ShiftRightCircular;
}
