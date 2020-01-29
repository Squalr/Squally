#include "SpecialShrCircular.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialShrCircular::SaveKeySpecialShrCircular = "special-shr-circular";

SpecialShrCircular* SpecialShrCircular::create()
{
	SpecialShrCircular* instance = new SpecialShrCircular();

	instance->autorelease();

	return instance;
}

SpecialShrCircular::SpecialShrCircular() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 3 }}), ItemMeta(3, 3))
{
}

SpecialShrCircular::~SpecialShrCircular()
{
}

Item* SpecialShrCircular::clone()
{
	return SpecialShrCircular::create();
}

std::string SpecialShrCircular::getItemName()
{
	return SpecialShrCircular::SaveKeySpecialShrCircular;
}

LocalizedString* SpecialShrCircular::getString()
{
	return Strings::Hexus_Cards_ShiftRightCircular::create();
}

std::string SpecialShrCircular::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialShrCircular::getSerializationKey()
{
	return SpecialShrCircular::SaveKeySpecialShrCircular;
}

std::string SpecialShrCircular::getCardKey()
{
	return CardKeys::ShiftRightCircular;
}
