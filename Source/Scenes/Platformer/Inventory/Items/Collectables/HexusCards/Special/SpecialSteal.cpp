#include "SpecialSteal.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Steal.h"

using namespace cocos2d;

const std::string SpecialSteal::SaveKeySpecialSteal = "special-steal";

SpecialSteal* SpecialSteal::create()
{
	SpecialSteal* instance = new SpecialSteal();

	instance->autorelease();

	return instance;
}

SpecialSteal::SpecialSteal() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}))
{
}

SpecialSteal::~SpecialSteal()
{
}

Item* SpecialSteal::clone()
{
	return SpecialSteal::create();
}

std::string SpecialSteal::getItemName()
{
	return SpecialSteal::SaveKeySpecialSteal;
}

LocalizedString* SpecialSteal::getString()
{
	return Strings::Hexus_Cards_Steal::create();
}

std::string SpecialSteal::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialSteal::getSerializationKey()
{
	return SpecialSteal::SaveKeySpecialSteal;
}

std::string SpecialSteal::getCardKey()
{
	return CardKeys::Steal;
}
