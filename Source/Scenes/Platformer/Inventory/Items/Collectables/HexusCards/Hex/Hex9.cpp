#include "Hex9.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Hex9.h"

using namespace cocos2d;

const std::string Hex9::SaveKeyHex9 = "hex-9";

Hex9* Hex9::create()
{
	Hex9* instance = new Hex9();

	instance->autorelease();

	return instance;
}

Hex9::Hex9() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
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
