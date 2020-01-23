#include "Hex4.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hex4::SaveKeyHex4 = "hex-4";

Hex4* Hex4::create()
{
	Hex4* instance = new Hex4();

	instance->autorelease();

	return instance;
}

Hex4::Hex4() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(3, 3))
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
	return Hex4::SaveKeyHex4;
}

LocalizedString* Hex4::getString()
{
	return Strings::Hexus_Cards_Hex4::create();
}

std::string Hex4::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex4::getSerializationKey()
{
	return Hex4::SaveKeyHex4;
}

std::string Hex4::getCardKey()
{
	return CardKeys::Hex4;
}
