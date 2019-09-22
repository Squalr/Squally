#include "Binary4.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Hexus/Cards/Binary4.h"

using namespace cocos2d;

const std::string Binary4::SaveKeyBinary4 = "binary-4";

Binary4* Binary4::create()
{
	Binary4* instance = new Binary4();

	instance->autorelease();

	return instance;
}

Binary4::Binary4() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Binary4::~Binary4()
{
}

Item* Binary4::clone()
{
	return Binary4::create();
}

std::string Binary4::getItemName()
{
	return Binary4::SaveKeyBinary4;
}

LocalizedString* Binary4::getString()
{
	return Strings::Hexus_Cards_Binary4::create();
}

std::string Binary4::getIconResource()
{
	return ObjectResources::Collectables_Cards_CardBinary;
}

std::string Binary4::getSerializationKey()
{
	return Binary4::SaveKeyBinary4;
}
