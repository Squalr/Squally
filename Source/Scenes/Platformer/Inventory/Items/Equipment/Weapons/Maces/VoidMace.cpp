#include "VoidMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidMace::SaveKey = "void-mace";

VoidMace* VoidMace::create()
{
	VoidMace* instance = new VoidMace();

	instance->autorelease();

	return instance;
}

VoidMace::VoidMace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), 6, 8, ItemStats(
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

VoidMace::~VoidMace()
{
}

Item* VoidMace::clone()
{
	return VoidMace::create();
}

std::string VoidMace::getItemName()
{
	return VoidMace::SaveKey;
}

LocalizedString* VoidMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_VoidMace::create();
}

std::string VoidMace::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_VoidMace;
}

std::string VoidMace::getSerializationKey()
{
	return VoidMace::SaveKey;
}

Vec2 VoidMace::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
