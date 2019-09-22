#include "Binary14.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Binary14.h"

using namespace cocos2d;

const std::string Binary14::SaveKeyBinary14 = "binary-14";

Binary14* Binary14::create()
{
	Binary14* instance = new Binary14();

	instance->autorelease();

	return instance;
}

Binary14::Binary14() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Binary14::~Binary14()
{
}

Item* Binary14::clone()
{
	return Binary14::create();
}

std::string Binary14::getItemName()
{
	return Binary14::SaveKeyBinary14;
}

LocalizedString* Binary14::getString()
{
	return Strings::Hexus_Cards_Binary14::create();
}

std::string Binary14::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary14::getSerializationKey()
{
	return Binary14::SaveKeyBinary14;
}
