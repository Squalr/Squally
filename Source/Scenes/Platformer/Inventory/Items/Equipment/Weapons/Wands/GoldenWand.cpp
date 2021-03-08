#include "GoldenWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/GoldenWandPlans.h"

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
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.15f
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

const std::string& GoldenWand::getItemName()
{
	return GoldenWand::SaveKey;
}

LocalizedString* GoldenWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_GoldenWand::create();
}

const std::string& GoldenWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_GoldenWand;
}

const std::string& GoldenWand::getSerializationKey()
{
	return GoldenWand::SaveKey;
}

Vec2 GoldenWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* GoldenWand::getRecipe()
{
	return GoldenWandPlans::create();
}
