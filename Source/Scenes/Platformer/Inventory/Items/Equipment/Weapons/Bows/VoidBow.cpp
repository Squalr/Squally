#include "VoidBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/VoidBowPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidBow::SaveKey = "void-bow";

VoidBow* VoidBow::create()
{
	VoidBow* instance = new VoidBow();

	instance->autorelease();

	return instance;
}

VoidBow::VoidBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 7 }}), BOW_DAMAGE_MIN(9), BOW_DAMAGE_MAX(9), ItemStats(
	// Health
	3,
	// Mana
	9,
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

VoidBow::~VoidBow()
{
}

Item* VoidBow::clone()
{
	return VoidBow::create();
}

LocalizedString* VoidBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_VoidBow::create();
}

const std::string& VoidBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_VoidBow;
}

const std::string& VoidBow::getIdentifier()
{
	return VoidBow::SaveKey;
}

Vec2 VoidBow::getDisplayOffset()
{
	return Vec2(-4.0f, -68.0f);
}

Recipe* VoidBow::getRecipe()
{
	return VoidBowPlans::create();
}
