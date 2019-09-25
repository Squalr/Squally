#include "Hex3.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Hex3.h"

using namespace cocos2d;

const std::string Hex3::SaveKeyHex3 = "hex-3";

Hex3* Hex3::create()
{
	Hex3* instance = new Hex3();

	instance->autorelease();

	return instance;
}

Hex3::Hex3() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
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
	return Hex3::SaveKeyHex3;
}

LocalizedString* Hex3::getString()
{
	return Strings::Hexus_Cards_Hex3::create();
}

std::string Hex3::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardHex;
}

std::string Hex3::getSerializationKey()
{
	return Hex3::SaveKeyHex3;
}
