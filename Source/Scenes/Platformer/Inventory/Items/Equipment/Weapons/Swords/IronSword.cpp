#include "IronSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Swords/IronSword.h"

using namespace cocos2d;

const std::string IronSword::SaveKeyIronSword = "iron-sword";

IronSword* IronSword::create()
{
	IronSword* instance = new IronSword();

	instance->autorelease();

	return instance;
}

IronSword::IronSword() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

IronSword::~IronSword()
{
}

Item* IronSword::clone()
{
	return IronSword::create();
}

std::string IronSword::getItemName()
{
	return IronSword::SaveKeyIronSword;
}

LocalizedString* IronSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_IronSword::create();
}

std::string IronSword::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_IronSword;
}

std::string IronSword::getSerializationKey()
{
	return IronSword::SaveKeyIronSword;
}
