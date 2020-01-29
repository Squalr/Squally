#include "Hex9.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex9::SaveKeyHex9 = "hex-9";

Hex9* Hex9::create()
{
	Hex9* instance = new Hex9();

	instance->autorelease();

	return instance;
}

Hex9::Hex9() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Hex9::~Hex9()
{
}

Item* Hex9::clone()
{
	return Hex9::create();
}

std::string Hex9::getItemName()
{
	return Hex9::SaveKeyHex9;
}

LocalizedString* Hex9::getString()
{
	return Strings::Hexus_Cards_Hex9::create();
}

std::string Hex9::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex9::getSerializationKey()
{
	return Hex9::SaveKeyHex9;
}

std::string Hex9::getCardKey()
{
	return CardKeys::Hex9;
}
