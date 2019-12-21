#include "Hex10.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex10::SaveKeyHex10 = "hex-10";

Hex10* Hex10::create()
{
	Hex10* instance = new Hex10();

	instance->autorelease();

	return instance;
}

Hex10::Hex10() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3))
{
}

Hex10::~Hex10()
{
}

Item* Hex10::clone()
{
	return Hex10::create();
}

std::string Hex10::getItemName()
{
	return Hex10::SaveKeyHex10;
}

LocalizedString* Hex10::getString()
{
	return Strings::Hexus_Cards_Hex10::create();
}

std::string Hex10::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex10::getSerializationKey()
{
	return Hex10::SaveKeyHex10;
}

std::string Hex10::getCardKey()
{
	return CardKeys::Hex10;
}
