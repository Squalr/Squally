#include "SpecialInv.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialInv::SaveKey = "special-inv";

SpecialInv* SpecialInv::create()
{
	SpecialInv* instance = new SpecialInv();

	instance->autorelease();

	return instance;
}

SpecialInv::SpecialInv() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 25 }}), ItemMeta(3, 3))
{
}

SpecialInv::~SpecialInv()
{
}

Item* SpecialInv::clone()
{
	return SpecialInv::create();
}

const std::string& SpecialInv::getItemName()
{
	return SpecialInv::SaveKey;
}

LocalizedString* SpecialInv::getString()
{
	return Strings::Hexus_Cards_Inverse::create();
}

const std::string& SpecialInv::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialInv::getSerializationKey()
{
	return SpecialInv::SaveKey;
}

std::string SpecialInv::getCardKey()
{
	return CardKeys::Inverse;
}
