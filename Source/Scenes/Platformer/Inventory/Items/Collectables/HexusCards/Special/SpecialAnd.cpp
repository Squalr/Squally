#include "SpecialAnd.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialAnd::SaveKeySpecialAnd = "special-and";

SpecialAnd* SpecialAnd::create()
{
	SpecialAnd* instance = new SpecialAnd();

	instance->autorelease();

	return instance;
}

SpecialAnd::SpecialAnd() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}), ItemMeta(3))
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
	return SpecialAnd::SaveKeySpecialAnd;
}

LocalizedString* SpecialAnd::getString()
{
	return Strings::Hexus_Cards_LogicalAnd::create();
}

std::string SpecialAnd::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialAnd::getSerializationKey()
{
	return SpecialAnd::SaveKeySpecialAnd;
}

std::string SpecialAnd::getCardKey()
{
	return CardKeys::LogicalAnd;
}
