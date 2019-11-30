#include "AshenBlade.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AshenBlade::SaveKeyAshenBlade = "ashen-blade";

AshenBlade* AshenBlade::create()
{
	AshenBlade* instance = new AshenBlade();

	instance->autorelease();

	return instance;
}

AshenBlade::AshenBlade() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

AshenBlade::~AshenBlade()
{
}

Item* AshenBlade::clone()
{
	return AshenBlade::create();
}

std::string AshenBlade::getItemName()
{
	return AshenBlade::SaveKeyAshenBlade;
}

LocalizedString* AshenBlade::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_AshenBlade::create();
}

std::string AshenBlade::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_AshenBlade;
}

std::string AshenBlade::getSerializationKey()
{
	return AshenBlade::SaveKeyAshenBlade;
}
