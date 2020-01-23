#include "SpecialAdd.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialAdd::SaveKeySpecialAdd = "special-add";

SpecialAdd* SpecialAdd::create()
{
	SpecialAdd* instance = new SpecialAdd();

	instance->autorelease();

	return instance;
}

SpecialAdd::SpecialAdd() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}), ItemMeta(3, 3))
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
	return SpecialAdd::SaveKeySpecialAdd;
}

LocalizedString* SpecialAdd::getString()
{
	return Strings::Hexus_Cards_Addition::create();
}

std::string SpecialAdd::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialAdd::getSerializationKey()
{
	return SpecialAdd::SaveKeySpecialAdd;
}

std::string SpecialAdd::getCardKey()
{
	return CardKeys::Addition;
}
