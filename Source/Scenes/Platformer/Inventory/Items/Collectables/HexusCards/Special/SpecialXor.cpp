#include "SpecialXor.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialXor::SaveKeySpecialXor = "special-xor";

SpecialXor* SpecialXor::create()
{
	SpecialXor* instance = new SpecialXor();

	instance->autorelease();

	return instance;
}

SpecialXor::SpecialXor() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}), ItemMeta(3, 3))
{
}

SpecialXor::~SpecialXor()
{
}

Item* SpecialXor::clone()
{
	return SpecialXor::create();
}

std::string SpecialXor::getItemName()
{
	return SpecialXor::SaveKeySpecialXor;
}

LocalizedString* SpecialXor::getString()
{
	return Strings::Hexus_Cards_LogicalXor::create();
}

std::string SpecialXor::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialXor::getSerializationKey()
{
	return SpecialXor::SaveKeySpecialXor;
}

std::string SpecialXor::getCardKey()
{
	return CardKeys::LogicalXor;
}
