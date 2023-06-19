#include "SteelHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier5/SteelHelmPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelHelm::SaveKey = "steel-helm";

SteelHelm* SteelHelm::create()
{
	SteelHelm* instance = new SteelHelm();

	instance->autorelease();

	return instance;
}

SteelHelm::SteelHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	WARRIOR_HP(5),
	// Mana
	WARRIOR_MP(5),
	// Attack
	WARRIOR_ATTACK(5),
	// Magic Attack
	WARRIOR_MAGIC_ATTACK(5),
	// Armor
	WARRIOR_ARMOR(5),
	// Speed
	WARRIOR_SPEED(5)
))
{
}

SteelHelm::~SteelHelm()
{
}

Item* SteelHelm::clone()
{
	return SteelHelm::create();
}

LocalizedString* SteelHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SteelHelm::create();
}

const std::string& SteelHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier5_SteelHelm;
}

const std::string& SteelHelm::getIdentifier()
{
	return SteelHelm::SaveKey;
}

Vec2 SteelHelm::getDisplayOffset()
{
	return Vec2(4.0f, -22.0f);
}

Recipe* SteelHelm::getRecipe()
{
	return SteelHelmPlans::create();
}
