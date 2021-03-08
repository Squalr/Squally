#include "SpecialGreed.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialGreed::SaveKey = "special-greed";

SpecialGreed* SpecialGreed::create()
{
	SpecialGreed* instance = new SpecialGreed();

	instance->autorelease();

	return instance;
}

SpecialGreed::SpecialGreed() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), ItemMeta(3, 3))
{
}

SpecialGreed::~SpecialGreed()
{
}

Item* SpecialGreed::clone()
{
	return SpecialGreed::create();
}

const std::string& SpecialGreed::getItemName()
{
	return SpecialGreed::SaveKey;
}

LocalizedString* SpecialGreed::getString()
{
	return Strings::Hexus_Cards_Greed::create();
}

const std::string& SpecialGreed::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialGreed::getIdentifier()
{
	return SpecialGreed::SaveKey;
}

std::string SpecialGreed::getCardKey()
{
	return CardKeys::Greed;
}
