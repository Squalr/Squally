#include "WizardsHatWater.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier4/WizardsHatWaterPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatWater::SaveKey = "wizards-hat-water";

WizardsHatWater* WizardsHatWater::create()
{
	WizardsHatWater* instance = new WizardsHatWater();

	instance->autorelease();

	return instance;
}

WizardsHatWater::WizardsHatWater() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	MAGE_HP(4),
	// Mana
	MAGE_MP(4),
	// Attack
	MAGE_ATTACK(4),
	// Magic Attack
	MAGE_MAGIC_ATTACK(4),
	// Armor
	MAGE_ARMOR(4),
	// Speed
	MAGE_SPEED(4)
))
{
}

WizardsHatWater::~WizardsHatWater()
{
}

Item* WizardsHatWater::clone()
{
	return WizardsHatWater::create();
}

LocalizedString* WizardsHatWater::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatWater::create();
}

const std::string& WizardsHatWater::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier4_WizardsHatWater;
}

const std::string& WizardsHatWater::getIdentifier()
{
	return WizardsHatWater::SaveKey;
}

Vec2 WizardsHatWater::getDisplayOffset()
{
	return Vec2(-20.0f, -8.0f);
}

Recipe* WizardsHatWater::getRecipe()
{
	return WizardsHatWaterPlans::create();
}
