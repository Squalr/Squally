#include "SteelBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelBow::SaveKey = "steel-bow";

SteelBow* SteelBow::create()
{
	SteelBow* instance = new SteelBow();

	instance->autorelease();

	return instance;
}

SteelBow::SteelBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 7 }}), 6, 8, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.25f
))
{
}

SteelBow::~SteelBow()
{
}

Item* SteelBow::clone()
{
	return SteelBow::create();
}

std::string SteelBow::getItemName()
{
	return SteelBow::SaveKey;
}

LocalizedString* SteelBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_SteelBow::create();
}

std::string SteelBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_SteelBow;
}

std::string SteelBow::getSerializationKey()
{
	return SteelBow::SaveKey;
}

Vec2 SteelBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
