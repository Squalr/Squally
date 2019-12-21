#include "SpecialAbsorb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialAbsorb::SaveKeySpecialAbsorb = "special-absorb";

SpecialAbsorb* SpecialAbsorb::create()
{
	SpecialAbsorb* instance = new SpecialAbsorb();

	instance->autorelease();

	return instance;
}

SpecialAbsorb::SpecialAbsorb() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 3 }}), ItemMeta(3))
{
}

SpecialAbsorb::~SpecialAbsorb()
{
}

Item* SpecialAbsorb::clone()
{
	return SpecialAbsorb::create();
}

std::string SpecialAbsorb::getItemName()
{
	return SpecialAbsorb::SaveKeySpecialAbsorb;
}

LocalizedString* SpecialAbsorb::getString()
{
	return Strings::Hexus_Cards_Absorb::create();
}

std::string SpecialAbsorb::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardSpecial;
}

std::string SpecialAbsorb::getSerializationKey()
{
	return SpecialAbsorb::SaveKeySpecialAbsorb;
}

std::string SpecialAbsorb::getCardKey()
{
	return CardKeys::Addition;
}
