#include "IronMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IronMace::SaveKeyIronMace = "iron-mace";

IronMace* IronMace::create()
{
	IronMace* instance = new IronMace();

	instance->autorelease();

	return instance;
}

IronMace::IronMace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 8, 14, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
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
	return ItemResources::Equipment_Weapons_Maces_IronMace;
}

std::string IronMace::getSerializationKey()
{
	return IronMace::SaveKeyIronMace;
}

Vec2 IronMace::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
