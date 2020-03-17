#include "SpecialMov.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialMov::SaveKeySpecialMov = "special-mov";

SpecialMov* SpecialMov::create()
{
	SpecialMov* instance = new SpecialMov();

	instance->autorelease();

	return instance;
}

SpecialMov::SpecialMov() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 3 }}), ItemMeta(3, 3))
{
}

SpecialMov::~SpecialMov()
{
}

Item* SpecialMov::clone()
{
	return SpecialMov::create();
}

std::string SpecialMov::getItemName()
{
	return SpecialMov::SaveKeySpecialMov;
}

LocalizedString* SpecialMov::getString()
{
	return Strings::Hexus_Cards_Mov::create();
}

std::string SpecialMov::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

std::string SpecialMov::getSerializationKey()
{
	return SpecialMov::SaveKeySpecialMov;
}

std::string SpecialMov::getCardKey()
{
	return CardKeys::Mov;
}
