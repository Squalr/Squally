#include "IronMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Maces/IronMace.h"

using namespace cocos2d;

const std::string IronMace::SaveKeyIronMace = "iron-mace";

IronMace* IronMace::create()
{
	IronMace* instance = new IronMace();

	instance->autorelease();

	return instance;
}

IronMace::IronMace() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

IronMace::~IronMace()
{
}

Item* IronMace::clone()
{
	return IronMace::create();
}

std::string IronMace::getItemName()
{
	return IronMace::SaveKeyIronMace;
}

LocalizedString* IronMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_IronMace::create();
}

std::string IronMace::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_IronMace;
}

std::string IronMace::getSerializationKey()
{
	return IronMace::SaveKeyIronMace;
}

Vec2 IronMace::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
