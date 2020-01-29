#include "FangBlade.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FangBlade::SaveKeyFangBlade = "fang-blade";

FangBlade* FangBlade::create()
{
	FangBlade* instance = new FangBlade();

	instance->autorelease();

	return instance;
}

FangBlade::FangBlade() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 3, 6, ItemStats(
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

FangBlade::~FangBlade()
{
}

Item* FangBlade::clone()
{
	return FangBlade::create();
}

std::string FangBlade::getItemName()
{
	return FangBlade::SaveKeyFangBlade;
}

LocalizedString* FangBlade::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_FangBlade::create();
}

std::string FangBlade::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_FangBlade;
}

std::string FangBlade::getSerializationKey()
{
	return FangBlade::SaveKeyFangBlade;
}
