#include "SpecialGreed.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialGreed::SaveKeySpecialGreed = "special-greed";

SpecialGreed* SpecialGreed::create()
{
	SpecialGreed* instance = new SpecialGreed();

	instance->autorelease();

	return instance;
}

SpecialGreed::SpecialGreed() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 3 }}), ItemMeta(3, 3))
{
}

SpecialGreed::~SpecialGreed()
{
}

Item* SpecialGreed::clone()
{
	return SpecialGreed::create();
}

std::string SpecialGreed::getItemName()
{
	return SpecialGreed::SaveKeySpecialGreed;
}

LocalizedString* SpecialGreed::getString()
{
	return Strings::Hexus_Cards_Greed::create();
}

std::string SpecialGreed::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialGreed::getSerializationKey()
{
	return SpecialGreed::SaveKeySpecialGreed;
}

std::string SpecialGreed::getCardKey()
{
	return CardKeys::Greed;
}
