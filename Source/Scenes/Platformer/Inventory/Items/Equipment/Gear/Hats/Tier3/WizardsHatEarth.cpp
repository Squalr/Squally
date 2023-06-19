#include "WizardsHatEarth.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier3/WizardsHatEarthPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatEarth::SaveKey = "wizards-hat-earth";

WizardsHatEarth* WizardsHatEarth::create()
{
	WizardsHatEarth* instance = new WizardsHatEarth();

	instance->autorelease();

	return instance;
}

WizardsHatEarth::WizardsHatEarth() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	MAGE_HP(3),
	// Mana
	MAGE_MP(3) + 1,
	// Attack
	MAGE_ATTACK(3),
	// Magic Attack
	MAGE_MAGIC_ATTACK(3),
	// Armor
	MAGE_ARMOR(3) + 1,
	// Speed
	MAGE_SPEED(3)
))
{
}

WizardsHatEarth::~WizardsHatEarth()
{
}

Item* WizardsHatEarth::clone()
{
	return WizardsHatEarth::create();
}

LocalizedString* WizardsHatEarth::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatEarth::create();
}

const std::string& WizardsHatEarth::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier3_WizardsHatEarth;
}

const std::string& WizardsHatEarth::getIdentifier()
{
	return WizardsHatEarth::SaveKey;
}

Vec2 WizardsHatEarth::getDisplayOffset()
{
	return Vec2(-18.0f, -8.0f);
}

Recipe* WizardsHatEarth::getRecipe()
{
	return WizardsHatEarthPlans::create();
}
