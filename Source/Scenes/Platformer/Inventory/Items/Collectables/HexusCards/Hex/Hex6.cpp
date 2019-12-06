#include "Hex6.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex6::SaveKeyHex6 = "hex-6";

Hex6* Hex6::create()
{
	Hex6* instance = new Hex6();

	instance->autorelease();

	return instance;
}

Hex6::Hex6() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3))
{
}

Hex6::~Hex6()
{
}

Item* Hex6::clone()
{
	return Hex6::create();
}

std::string Hex6::getItemName()
{
	return Hex6::SaveKeyHex6;
}

LocalizedString* Hex6::getString()
{
	return Strings::Hexus_Cards_Hex6::create();
}

std::string Hex6::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex6::getSerializationKey()
{
	return Hex6::SaveKeyHex6;
}

std::string Hex6::getCardKey()
{
	return CardKeys::Hex6;
}
