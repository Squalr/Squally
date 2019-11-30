#include "Hex14.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex14::SaveKeyHex14 = "hex-14";

Hex14* Hex14::create()
{
	Hex14* instance = new Hex14();

	instance->autorelease();

	return instance;
}

Hex14::Hex14() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Hex14::~Hex14()
{
}

Item* Hex14::clone()
{
	return Hex14::create();
}

std::string Hex14::getItemName()
{
	return Hex14::SaveKeyHex14;
}

LocalizedString* Hex14::getString()
{
	return Strings::Hexus_Cards_Hex14::create();
}

std::string Hex14::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex14::getSerializationKey()
{
	return Hex14::SaveKeyHex14;
}

std::string Hex14::getCardKey()
{
	return CardKeys::Hex14;
}
