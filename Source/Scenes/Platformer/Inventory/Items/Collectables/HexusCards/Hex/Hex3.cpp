#include "Hex3.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex3::SaveKey = "hex-3";

Hex3* Hex3::create()
{
	Hex3* instance = new Hex3();

	instance->autorelease();

	return instance;
}

Hex3::Hex3() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 4 }}), ItemMeta(3, 3))
{
}

Hex3::~Hex3()
{
}

Item* Hex3::clone()
{
	return Hex3::create();
}

std::string Hex3::getItemName()
{
	return Hex3::SaveKey;
}

LocalizedString* Hex3::getString()
{
	return Strings::Hexus_Cards_Hex3::create();
}

std::string Hex3::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

std::string Hex3::getSerializationKey()
{
	return Hex3::SaveKey;
}

std::string Hex3::getCardKey()
{
	return CardKeys::Hex3;
}
