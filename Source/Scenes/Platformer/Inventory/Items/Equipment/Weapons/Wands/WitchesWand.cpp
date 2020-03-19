#include "WitchesWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WitchesWand::SaveKey = "witches-wand";

WitchesWand* WitchesWand::create()
{
	WitchesWand* instance = new WitchesWand();

	instance->autorelease();

	return instance;
}

WitchesWand::WitchesWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 28, ItemStats(
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

WitchesWand::~WitchesWand()
{
}

Item* WitchesWand::clone()
{
	return WitchesWand::create();
}

std::string WitchesWand::getItemName()
{
	return WitchesWand::SaveKey;
}

LocalizedString* WitchesWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_WitchesWand::create();
}

std::string WitchesWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_WitchesWand;
}

std::string WitchesWand::getSerializationKey()
{
	return WitchesWand::SaveKey;
}

Vec2 WitchesWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
