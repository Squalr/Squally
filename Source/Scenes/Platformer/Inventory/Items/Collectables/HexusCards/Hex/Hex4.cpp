#include "Hex4.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex4::SaveKey = "hex-4";

Hex4* Hex4::create()
{
	Hex4* instance = new Hex4();

	instance->autorelease();

	return instance;
}

Hex4::Hex4() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(3, 3))
{
}

Hex4::~Hex4()
{
}

Item* Hex4::clone()
{
	return Hex4::create();
}

std::string Hex4::getItemName()
{
	return Hex4::SaveKey;
}

LocalizedString* Hex4::getString()
{
	return Strings::Hexus_Cards_Hex4::create();
}

std::string Hex4::getIconResource()
{
	return ItemResources::Collectables_Cards_CardHex;
}

std::string Hex4::getSerializationKey()
{
	return Hex4::SaveKey;
}

std::string Hex4::getCardKey()
{
	return CardKeys::Hex4;
}
