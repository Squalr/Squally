#include "MagesHatRed.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier3/MagesHatRedPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MagesHatRed::SaveKey = "mages-hat-red";

MagesHatRed* MagesHatRed::create()
{
	MagesHatRed* instance = new MagesHatRed();

	instance->autorelease();

	return instance;
}

MagesHatRed::MagesHatRed() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

MagesHatRed::~MagesHatRed()
{
}

Item* MagesHatRed::clone()
{
	return MagesHatRed::create();
}

LocalizedString* MagesHatRed::getString()
{
	return Strings::Items_Equipment_Gear_Hats_MagesHatRed::create();
}

const std::string& MagesHatRed::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_MagesHatRed;
}

const std::string& MagesHatRed::getIdentifier()
{
	return MagesHatRed::SaveKey;
}

Vec2 MagesHatRed::getDisplayOffset()
{
	return Vec2(-36.0f, -12.0f);
}

Recipe* MagesHatRed::getRecipe()
{
	return MagesHatRedPlans::create();
}
