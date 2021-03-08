#include "Hex14.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex14::SaveKey = "hex-14";

Hex14* Hex14::create()
{
	Hex14* instance = new Hex14();

	instance->autorelease();

	return instance;
}

Hex14::Hex14() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 18 }}), ItemMeta(3, 3))
{
}

Hex14::~Hex14()
{
}

Item* Hex14::clone()
{
	return Hex14::create();
}

const std::string& Hex14::getItemName()
{
	return Hex14::SaveKey;
}

LocalizedString* Hex14::getString()
{
	return Strings::Hexus_Cards_Hex14::create();
}

const std::string& Hex14::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

const std::string& Hex14::getSerializationKey()
{
	return Hex14::SaveKey;
}

std::string Hex14::getCardKey()
{
	return CardKeys::Hex14;
}
