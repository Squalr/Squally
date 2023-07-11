#include "SilverWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/SilverWandPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SilverWand::SaveKey = "silver-wand";

SilverWand* SilverWand::create()
{
	SilverWand* instance = new SilverWand();

	instance->autorelease();

	return instance;
}

SilverWand::SilverWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), WAND_DAMAGE_MIN(3), WAND_DAMAGE_MAX(3), ItemStats(
	// Health
	0,
	// Mana
	9,
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

SilverWand::~SilverWand()
{
}

Item* SilverWand::clone()
{
	return SilverWand::create();
}

LocalizedString* SilverWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_SilverWand::create();
}

const std::string& SilverWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_SilverWand;
}

const std::string& SilverWand::getIdentifier()
{
	return SilverWand::SaveKey;
}

Vec2 SilverWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* SilverWand::getRecipe()
{
	return SilverWandPlans::create();
}
