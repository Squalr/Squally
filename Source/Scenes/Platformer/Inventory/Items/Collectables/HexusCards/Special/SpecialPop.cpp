#include "SpecialPop.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialPop::SaveKey = "special-pop";

SpecialPop* SpecialPop::create()
{
	SpecialPop* instance = new SpecialPop();

	instance->autorelease();

	return instance;
}

SpecialPop::SpecialPop() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 9 }}), ItemMeta(3, 3))
{
}

SpecialPop::~SpecialPop()
{
}

Item* SpecialPop::clone()
{
	return SpecialPop::create();
}

LocalizedString* SpecialPop::getString()
{
	return Strings::Hexus_Cards_Pop::create();
}

const std::string& SpecialPop::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialPop::getIdentifier()
{
	return SpecialPop::SaveKey;
}

std::string SpecialPop::getCardKey()
{
	return CardKeys::Pop;
}
