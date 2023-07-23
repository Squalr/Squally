#include "WizardsHatArcane.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier7/WizardsHatArcanePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatArcane::SaveKey = "wizards-hat-arcane";

WizardsHatArcane* WizardsHatArcane::create()
{
	WizardsHatArcane* instance = new WizardsHatArcane();

	instance->autorelease();

	return instance;
}

WizardsHatArcane::WizardsHatArcane() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	MAGE_HP(7),
	// Mana
	MAGE_MP(7),
	// Attack
	MAGE_ATTACK(7),
	// Magic Attack
	MAGE_MAGIC_ATTACK(7),
	// Armor
	MAGE_ARMOR(7),
	// Speed
	MAGE_SPEED(7)
))
{
}

WizardsHatArcane::~WizardsHatArcane()
{
}

Item* WizardsHatArcane::clone()
{
	return WizardsHatArcane::create();
}

LocalizedString* WizardsHatArcane::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatArcane::create();
}

const std::string& WizardsHatArcane::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier7_WizardsHatArcane;
}

const std::string& WizardsHatArcane::getIdentifier()
{
	return WizardsHatArcane::SaveKey;
}

Vec2 WizardsHatArcane::getDisplayOffset()
{
	return Vec2(-22.0f, -8.0f);
}

Recipe* WizardsHatArcane::getRecipe()
{
	return WizardsHatArcanePlans::create();
}
