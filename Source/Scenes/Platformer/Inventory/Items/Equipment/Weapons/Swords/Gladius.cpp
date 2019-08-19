#include "Gladius.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Swords/Gladius.h"

using namespace cocos2d;

const std::string Gladius::SaveKeyGladius = "gladius";

Gladius* Gladius::create()
{
	Gladius* instance = new Gladius();

	instance->autorelease();

	return instance;
}

Gladius::Gladius() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

Gladius::~Gladius()
{
}

Item* Gladius::clone()
{
	return Gladius::create();
}

std::string Gladius::getItemName()
{
	return Gladius::SaveKeyGladius;
}

LocalizedString* Gladius::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Gladius::create();
}

std::string Gladius::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_Gladius;
}

std::string Gladius::getSerializationKey()
{
	return Gladius::SaveKeyGladius;
}
