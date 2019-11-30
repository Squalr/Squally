#include "WarCutlas.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WarCutlas::SaveKeyWarCutlas = "war-cutlas";

WarCutlas* WarCutlas::create()
{
	WarCutlas* instance = new WarCutlas();

	instance->autorelease();

	return instance;
}

WarCutlas::WarCutlas() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

WarCutlas::~WarCutlas()
{
}

Item* WarCutlas::clone()
{
	return WarCutlas::create();
}

std::string WarCutlas::getItemName()
{
	return WarCutlas::SaveKeyWarCutlas;
}

LocalizedString* WarCutlas::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_WarCutlas::create();
}

std::string WarCutlas::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_WarCutlas;
}

std::string WarCutlas::getSerializationKey()
{
	return WarCutlas::SaveKeyWarCutlas;
}
