#include "Hex5.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Hex5.h"

using namespace cocos2d;

const std::string Hex5::SaveKeyHex5 = "hex-5";

Hex5* Hex5::create()
{
	Hex5* instance = new Hex5();

	instance->autorelease();

	return instance;
}

Hex5::Hex5() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Hex5::~Hex5()
{
}

Item* Hex5::clone()
{
	return Hex5::create();
}

std::string Hex5::getItemName()
{
	return Hex5::SaveKeyHex5;
}

LocalizedString* Hex5::getString()
{
	return Strings::Hexus_Cards_Hex5::create();
}

std::string Hex5::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex5::getSerializationKey()
{
	return Hex5::SaveKeyHex5;
}

std::string Hex5::getCardKey()
{
	return CardKeys::Hex5;
}
