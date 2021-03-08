#include "SpecialSteal.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialSteal::SaveKey = "special-steal";

SpecialSteal* SpecialSteal::create()
{
	SpecialSteal* instance = new SpecialSteal();

	instance->autorelease();

	return instance;
}

SpecialSteal::SpecialSteal() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 23 }}), ItemMeta(3, 3))
{
}

SpecialSteal::~SpecialSteal()
{
}

Item* SpecialSteal::clone()
{
	return SpecialSteal::create();
}

const std::string& SpecialSteal::getItemName()
{
	return SpecialSteal::SaveKey;
}

LocalizedString* SpecialSteal::getString()
{
	return Strings::Hexus_Cards_Steal::create();
}

const std::string& SpecialSteal::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialSteal::getSerializationKey()
{
	return SpecialSteal::SaveKey;
}

std::string SpecialSteal::getCardKey()
{
	return CardKeys::Steal;
}
