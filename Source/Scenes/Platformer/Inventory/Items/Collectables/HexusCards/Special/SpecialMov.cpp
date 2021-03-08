#include "SpecialMov.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialMov::SaveKey = "special-mov";

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

const std::string& SpecialMov::getItemName()
{
	return SpecialMov::SaveKey;
}

LocalizedString* SpecialMov::getString()
{
	return Strings::Hexus_Cards_Mov::create();
}

const std::string& SpecialMov::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialMov::getIdentifier()
{
	return SpecialMov::SaveKey;
}

std::string SpecialMov::getCardKey()
{
	return CardKeys::Mov;
}
