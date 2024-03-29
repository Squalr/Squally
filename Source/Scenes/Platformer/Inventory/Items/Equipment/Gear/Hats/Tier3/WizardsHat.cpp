#include "WizardsHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier3/WizardsHatPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHat::SaveKey = "wizards-hat";

WizardsHat* WizardsHat::create()
{
	WizardsHat* instance = new WizardsHat();

	instance->autorelease();

	return instance;
}

WizardsHat::WizardsHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	MAGE_HP(3),
	// Mana
	MAGE_MP(3),
	// Attack
	MAGE_ATTACK(3),
	// Magic Attack
	MAGE_MAGIC_ATTACK(3),
	// Armor
	MAGE_ARMOR(3),
	// Speed
	MAGE_SPEED(3)
))
{
}

WizardsHat::~WizardsHat()
{
}

Item* WizardsHat::clone()
{
	return WizardsHat::create();
}

LocalizedString* WizardsHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHat::create();
}

const std::string& WizardsHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier3_WizardsHat;
}

const std::string& WizardsHat::getIdentifier()
{
	return WizardsHat::SaveKey;
}

Vec2 WizardsHat::getDisplayOffset()
{
	return Vec2(-22.0f, -8.0f);
}

Recipe* WizardsHat::getRecipe()
{
	return WizardsHatPlans::create();
}
