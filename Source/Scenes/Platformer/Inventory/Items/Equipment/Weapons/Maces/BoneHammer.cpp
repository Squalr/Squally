#include "BoneHammer.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/BoneHammerPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneHammer::SaveKey = "bone-hammer";

BoneHammer* BoneHammer::create()
{
	BoneHammer* instance = new BoneHammer();

	instance->autorelease();

	return instance;
}

BoneHammer::BoneHammer() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 48, 56, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

BoneHammer::~BoneHammer()
{
}

Item* BoneHammer::clone()
{
	return BoneHammer::create();
}

LocalizedString* BoneHammer::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_BoneHammer::create();
}

const std::string& BoneHammer::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_BoneHammer;
}

const std::string& BoneHammer::getIdentifier()
{
	return BoneHammer::SaveKey;
}

Vec2 BoneHammer::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* BoneHammer::getRecipe()
{
	return BoneHammerPlans::create();
}
