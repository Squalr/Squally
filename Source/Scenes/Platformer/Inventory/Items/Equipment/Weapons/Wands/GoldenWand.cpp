#include "GoldenWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenWand::SaveKey = "golden-wand";

GoldenWand* GoldenWand::create()
{
	GoldenWand* instance = new GoldenWand();

	instance->autorelease();

	return instance;
}

GoldenWand::GoldenWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 28, ItemStats(
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

GoldenWand::~GoldenWand()
{
}

Item* GoldenWand::clone()
{
	return GoldenWand::create();
}

std::string GoldenWand::getItemName()
{
	return GoldenWand::SaveKey;
}

LocalizedString* GoldenWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_GoldenWand::create();
}

std::string GoldenWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_GoldenWand;
}

std::string GoldenWand::getSerializationKey()
{
	return GoldenWand::SaveKey;
}

Vec2 GoldenWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
