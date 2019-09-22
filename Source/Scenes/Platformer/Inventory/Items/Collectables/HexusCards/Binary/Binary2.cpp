#include "Binary2.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Binary2.h"

using namespace cocos2d;

const std::string Binary2::SaveKeyBinary2 = "binary-2";

Binary2* Binary2::create()
{
	Binary2* instance = new Binary2();

	instance->autorelease();

	return instance;
}

Binary2::Binary2() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Binary2::~Binary2()
{
}

Item* Binary2::clone()
{
	return Binary2::create();
}

std::string Binary2::getItemName()
{
	return Binary2::SaveKeyBinary2;
}

LocalizedString* Binary2::getString()
{
	return Strings::Hexus_Cards_Binary2::create();
}

std::string Binary2::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary2::getSerializationKey()
{
	return Binary2::SaveKeyBinary2;
}
