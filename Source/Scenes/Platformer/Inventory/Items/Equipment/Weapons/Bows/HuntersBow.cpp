#include "HuntersBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HuntersBow::SaveKey = "hunters-bow";

HuntersBow* HuntersBow::create()
{
	HuntersBow* instance = new HuntersBow();

	instance->autorelease();

	return instance;
}

HuntersBow::HuntersBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 8, 12, ItemStats(
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

HuntersBow::~HuntersBow()
{
}

Item* HuntersBow::clone()
{
	return HuntersBow::create();
}

std::string HuntersBow::getItemName()
{
	return HuntersBow::SaveKey;
}

LocalizedString* HuntersBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_HuntersBow::create();
}

std::string HuntersBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_HuntersBow;
}

std::string HuntersBow::getSerializationKey()
{
	return HuntersBow::SaveKey;
}

Vec2 HuntersBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
