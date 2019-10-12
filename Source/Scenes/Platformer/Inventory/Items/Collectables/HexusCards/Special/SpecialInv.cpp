#include "SpecialInv.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Inverse.h"

using namespace cocos2d;

const std::string SpecialInv::SaveKeySpecialInv = "special-inv";

SpecialInv* SpecialInv::create()
{
	SpecialInv* instance = new SpecialInv();

	instance->autorelease();

	return instance;
}

SpecialInv::SpecialInv() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}))
{
}

SpecialInv::~SpecialInv()
{
}

Item* SpecialInv::clone()
{
	return SpecialInv::create();
}

std::string SpecialInv::getItemName()
{
	return SpecialInv::SaveKeySpecialInv;
}

LocalizedString* SpecialInv::getString()
{
	return Strings::Hexus_Cards_Inverse::create();
}

std::string SpecialInv::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialInv::getSerializationKey()
{
	return SpecialInv::SaveKeySpecialInv;
}

std::string SpecialInv::getCardKey()
{
	return CardKeys::Inverse;
}
