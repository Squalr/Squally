#include "SpecialShl.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialShl::SaveKey = "special-shl";

SpecialShl* SpecialShl::create()
{
	SpecialShl* instance = new SpecialShl();

	instance->autorelease();

	return instance;
}

SpecialShl::SpecialShl() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), ItemMeta(3, 3))
{
}

SpecialShl::~SpecialShl()
{
}

Item* SpecialShl::clone()
{
	return SpecialShl::create();
}

LocalizedString* SpecialShl::getString()
{
	return Strings::Hexus_Cards_ShiftLeft::create();
}

const std::string& SpecialShl::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialShl::getIdentifier()
{
	return SpecialShl::SaveKey;
}

std::string SpecialShl::getCardKey()
{
	return CardKeys::ShiftLeft;
}
