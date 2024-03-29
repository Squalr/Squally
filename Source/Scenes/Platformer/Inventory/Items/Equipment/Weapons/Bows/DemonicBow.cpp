#include "DemonicBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/DemonicBowPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonicBow::SaveKey = "demonic-bow";

DemonicBow* DemonicBow::create()
{
	DemonicBow* instance = new DemonicBow();

	instance->autorelease();

	return instance;
}

DemonicBow::DemonicBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), BOW_DAMAGE_MIN(7), BOW_DAMAGE_MAX(7), ItemStats(
	// Health
	2,
	// Mana
	7,
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

DemonicBow::~DemonicBow()
{
}

Item* DemonicBow::clone()
{
	return DemonicBow::create();
}

LocalizedString* DemonicBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_DemonicBow::create();
}

const std::string& DemonicBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_DemonicBow;
}

const std::string& DemonicBow::getIdentifier()
{
	return DemonicBow::SaveKey;
}

Vec2 DemonicBow::getDisplayOffset()
{
	return Vec2(-10.0f, -66.0f);
}

Recipe* DemonicBow::getRecipe()
{
	return DemonicBowPlans::create();
}
