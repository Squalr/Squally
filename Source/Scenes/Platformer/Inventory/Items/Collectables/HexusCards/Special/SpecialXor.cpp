#include "SpecialXor.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialXor::SaveKey = "special-xor";

SpecialXor* SpecialXor::create()
{
	SpecialXor* instance = new SpecialXor();

	instance->autorelease();

	return instance;
}

SpecialXor::SpecialXor() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 18 }}), ItemMeta(3, 3))
{
}

SpecialXor::~SpecialXor()
{
}

Item* SpecialXor::clone()
{
	return SpecialXor::create();
}

LocalizedString* SpecialXor::getString()
{
	return Strings::Hexus_Cards_LogicalXor::create();
}

const std::string& SpecialXor::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialXor::getIdentifier()
{
	return SpecialXor::SaveKey;
}

std::string SpecialXor::getCardKey()
{
	return CardKeys::LogicalXor;
}
