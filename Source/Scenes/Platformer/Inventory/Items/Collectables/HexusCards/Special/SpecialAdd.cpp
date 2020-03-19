#include "SpecialAdd.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialAdd::SaveKey = "special-add";

SpecialAdd* SpecialAdd::create()
{
	SpecialAdd* instance = new SpecialAdd();

	instance->autorelease();

	return instance;
}

SpecialAdd::SpecialAdd() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 3 }}), ItemMeta(3, 3))
{
}

SpecialAdd::~SpecialAdd()
{
}

Item* SpecialAdd::clone()
{
	return SpecialAdd::create();
}

std::string SpecialAdd::getItemName()
{
	return SpecialAdd::SaveKey;
}

LocalizedString* SpecialAdd::getString()
{
	return Strings::Hexus_Cards_Addition::create();
}

std::string SpecialAdd::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

std::string SpecialAdd::getSerializationKey()
{
	return SpecialAdd::SaveKey;
}

std::string SpecialAdd::getCardKey()
{
	return CardKeys::Addition;
}
