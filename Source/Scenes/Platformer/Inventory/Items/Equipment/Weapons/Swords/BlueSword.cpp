#include "BlueSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Swords/BlueSword.h"

using namespace cocos2d;

const std::string BlueSword::SaveKeyBlueSword = "blue-sword";

BlueSword* BlueSword::create()
{
	BlueSword* instance = new BlueSword();

	instance->autorelease();

	return instance;
}

BlueSword::BlueSword() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

BlueSword::~BlueSword()
{
}

Item* BlueSword::clone()
{
	return BlueSword::create();
}

std::string BlueSword::getItemName()
{
	return BlueSword::SaveKeyBlueSword;
}

LocalizedString* BlueSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_BlueSword::create();
}

std::string BlueSword::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_BlueSword;
}

std::string BlueSword::getSerializationKey()
{
	return BlueSword::SaveKeyBlueSword;
}
