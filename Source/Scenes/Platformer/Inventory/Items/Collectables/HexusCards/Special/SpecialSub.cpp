#include "SpecialSub.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialSub::SaveKey = "special-sub";

SpecialSub* SpecialSub::create()
{
	SpecialSub* instance = new SpecialSub();

	instance->autorelease();

	return instance;
}

SpecialSub::SpecialSub() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 8 }}), ItemMeta(3, 3))
{
}

SpecialSub::~SpecialSub()
{
}

Item* SpecialSub::clone()
{
	return SpecialSub::create();
}

const std::string& SpecialSub::getItemName()
{
	return SpecialSub::SaveKey;
}

LocalizedString* SpecialSub::getString()
{
	return Strings::Hexus_Cards_Subtract::create();
}

const std::string& SpecialSub::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialSub::getIdentifier()
{
	return SpecialSub::SaveKey;
}

std::string SpecialSub::getCardKey()
{
	return CardKeys::Subtraction;
}
