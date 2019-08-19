#include "SteelSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Swords/SteelSword.h"

using namespace cocos2d;

const std::string SteelSword::SaveKeySteelSword = "steel-sword";

SteelSword* SteelSword::create()
{
	SteelSword* instance = new SteelSword();

	instance->autorelease();

	return instance;
}

SteelSword::SteelSword() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

SteelSword::~SteelSword()
{
}

Item* SteelSword::clone()
{
	return SteelSword::create();
}

std::string SteelSword::getItemName()
{
	return SteelSword::SaveKeySteelSword;
}

LocalizedString* SteelSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_SteelSword::create();
}

std::string SteelSword::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_SteelSword;
}

std::string SteelSword::getSerializationKey()
{
	return SteelSword::SaveKeySteelSword;
}
