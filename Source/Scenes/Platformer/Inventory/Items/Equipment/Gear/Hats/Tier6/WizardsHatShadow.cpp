#include "WizardsHatShadow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier6/WizardsHatShadowPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatShadow::SaveKey = "wizards-hat-shadow";

WizardsHatShadow* WizardsHatShadow::create()
{
	WizardsHatShadow* instance = new WizardsHatShadow();

	instance->autorelease();

	return instance;
}

WizardsHatShadow::WizardsHatShadow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	MAGE_HP(6),
	// Mana
	MAGE_MP(6),
	// Attack
	MAGE_ATTACK(6),
	// Magic Attack
	MAGE_MAGIC_ATTACK(6),
	// Armor
	MAGE_ARMOR(6),
	// Speed
	MAGE_SPEED(6)
))
{
}

WizardsHatShadow::~WizardsHatShadow()
{
}

Item* WizardsHatShadow::clone()
{
	return WizardsHatShadow::create();
}

LocalizedString* WizardsHatShadow::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatShadow::create();
}

const std::string& WizardsHatShadow::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier6_WizardsHatShadow;
}

const std::string& WizardsHatShadow::getIdentifier()
{
	return WizardsHatShadow::SaveKey;
}

Vec2 WizardsHatShadow::getDisplayOffset()
{
	return Vec2(-22.0f, -10.0f);
}

Recipe* WizardsHatShadow::getRecipe()
{
	return WizardsHatShadowPlans::create();
}
