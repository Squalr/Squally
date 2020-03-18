#include "WoodBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodBow::SaveKeyWoodBow = "wood-bow";

WoodBow* WoodBow::create()
{
	WoodBow* instance = new WoodBow();

	instance->autorelease();

	return instance;
}

WoodBow::WoodBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 6, 8, ItemStats(
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

WoodBow::~WoodBow()
{
}

Item* WoodBow::clone()
{
	return WoodBow::create();
}

std::string WoodBow::getItemName()
{
	return WoodBow::SaveKeyWoodBow;
}

LocalizedString* WoodBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_WoodBow::create();
}

std::string WoodBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_WoodBow;
}

std::string WoodBow::getSerializationKey()
{
	return WoodBow::SaveKeyWoodBow;
}

Vec2 WoodBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
