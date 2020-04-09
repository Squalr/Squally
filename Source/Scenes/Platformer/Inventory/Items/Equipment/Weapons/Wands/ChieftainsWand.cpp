#include "ChieftainsWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ChieftainsWand::SaveKey = "chieftains-wand";

ChieftainsWand* ChieftainsWand::create()
{
	ChieftainsWand* instance = new ChieftainsWand();

	instance->autorelease();

	return instance;
}

ChieftainsWand::ChieftainsWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 20, 24, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.15f
))
{
}

ChieftainsWand::~ChieftainsWand()
{
}

Item* ChieftainsWand::clone()
{
	return ChieftainsWand::create();
}

std::string ChieftainsWand::getItemName()
{
	return ChieftainsWand::SaveKey;
}

LocalizedString* ChieftainsWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_ChieftainsWand::create();
}

std::string ChieftainsWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_ChieftainsWand;
}

std::string ChieftainsWand::getSerializationKey()
{
	return ChieftainsWand::SaveKey;
}

Vec2 ChieftainsWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
