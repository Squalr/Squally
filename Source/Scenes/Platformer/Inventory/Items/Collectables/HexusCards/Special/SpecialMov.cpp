#include "SpecialMov.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialMov::SaveKeySpecialMov = "special-mov";

SpecialMov* SpecialMov::create()
{
	SpecialMov* instance = new SpecialMov();

	instance->autorelease();

	return instance;
}

SpecialMov::SpecialMov() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}), ItemMeta(3))
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
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialMov::getSerializationKey()
{
	return SpecialMov::SaveKeySpecialMov;
}

std::string SpecialMov::getCardKey()
{
	return CardKeys::Mov;
}
