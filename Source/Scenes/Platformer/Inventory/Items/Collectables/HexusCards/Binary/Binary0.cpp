#include "Binary0.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Binary0.h"

using namespace cocos2d;

const std::string Binary0::SaveKeyBinary0 = "binary-0";

Binary0* Binary0::create()
{
	Binary0* instance = new Binary0();

	instance->autorelease();

	return instance;
}

Binary0::Binary0() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Binary0::~Binary0()
{
}

Item* Binary0::clone()
{
	return Binary0::create();
}

std::string Binary0::getItemName()
{
	return Binary0::SaveKeyBinary0;
}

LocalizedString* Binary0::getString()
{
	return Strings::Hexus_Cards_Binary0::create();
}

std::string Binary0::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary0::getSerializationKey()
{
	return Binary0::SaveKeyBinary0;
}
