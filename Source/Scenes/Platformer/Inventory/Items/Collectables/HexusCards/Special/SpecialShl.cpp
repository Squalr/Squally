#include "SpecialShl.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialShl::SaveKeySpecialShl = "special-shl";

SpecialShl* SpecialShl::create()
{
	SpecialShl* instance = new SpecialShl();

	instance->autorelease();

	return instance;
}

SpecialShl::SpecialShl() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}), ItemMeta(3, 3))
{
}

SpecialShl::~SpecialShl()
{
}

Item* SpecialShl::clone()
{
	return SpecialShl::create();
}

std::string SpecialShl::getItemName()
{
	return SpecialShl::SaveKeySpecialShl;
}

LocalizedString* SpecialShl::getString()
{
	return Strings::Hexus_Cards_ShiftLeft::create();
}

std::string SpecialShl::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialShl::getSerializationKey()
{
	return SpecialShl::SaveKeySpecialShl;
}

std::string SpecialShl::getCardKey()
{
	return CardKeys::ShiftLeft;
}
