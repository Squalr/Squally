#include "Hex7.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex7::SaveKeyHex7 = "hex-7";

Hex7* Hex7::create()
{
	Hex7* instance = new Hex7();

	instance->autorelease();

	return instance;
}

Hex7::Hex7() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Hex7::~Hex7()
{
}

Item* Hex7::clone()
{
	return Hex7::create();
}

std::string Hex7::getItemName()
{
	return Hex7::SaveKeyHex7;
}

LocalizedString* Hex7::getString()
{
	return Strings::Hexus_Cards_Hex7::create();
}

std::string Hex7::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex7::getSerializationKey()
{
	return Hex7::SaveKeyHex7;
}

std::string Hex7::getCardKey()
{
	return CardKeys::Hex7;
}
