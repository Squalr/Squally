#include "MagesHatBlue.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier3/MagesHatBluePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MagesHatBlue::SaveKey = "mages-hat-blue";

MagesHatBlue* MagesHatBlue::create()
{
	MagesHatBlue* instance = new MagesHatBlue();

	instance->autorelease();

	return instance;
}

MagesHatBlue::MagesHatBlue() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

MagesHatBlue::~MagesHatBlue()
{
}

Item* MagesHatBlue::clone()
{
	return MagesHatBlue::create();
}

LocalizedString* MagesHatBlue::getString()
{
	return Strings::Items_Equipment_Gear_Hats_MagesHatBlue::create();
}

const std::string& MagesHatBlue::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_MagesHatBlue;
}

const std::string& MagesHatBlue::getIdentifier()
{
	return MagesHatBlue::SaveKey;
}

Vec2 MagesHatBlue::getDisplayOffset()
{
	return Vec2(-36.0f, -12.0f);
}

Recipe* MagesHatBlue::getRecipe()
{
	return MagesHatBluePlans::create();
}
