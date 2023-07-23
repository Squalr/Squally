#include "VikingHelmet.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier7/VikingHelmetPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VikingHelmet::SaveKey = "viking-helmet";

VikingHelmet* VikingHelmet::create()
{
	VikingHelmet* instance = new VikingHelmet();

	instance->autorelease();

	return instance;
}

VikingHelmet::VikingHelmet() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 17 }}), ItemStats(
	// Health
	WARRIOR_HP(7),
	// Mana
	WARRIOR_MP(7),
	// Attack
	WARRIOR_ATTACK(7),
	// Magic Attack
	WARRIOR_MAGIC_ATTACK(7),
	// Armor
	WARRIOR_ARMOR(7),
	// Speed
	WARRIOR_SPEED(7)
))
{
}

VikingHelmet::~VikingHelmet()
{
}

Item* VikingHelmet::clone()
{
	return VikingHelmet::create();
}

LocalizedString* VikingHelmet::getString()
{
	return Strings::Items_Equipment_Gear_Hats_VikingHelmet::create();
}

const std::string& VikingHelmet::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier7_VikingHelmet;
}

const std::string& VikingHelmet::getIdentifier()
{
	return VikingHelmet::SaveKey;
}

Vec2 VikingHelmet::getDisplayOffset()
{
	return Vec2(-2.0f, -16.0f);
}

Recipe* VikingHelmet::getRecipe()
{
	return VikingHelmetPlans::create();
}
