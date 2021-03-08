#include "TaserRod.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/TaserRodPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TaserRod::SaveKey = "taser-rod";

TaserRod* TaserRod::create()
{
	TaserRod* instance = new TaserRod();

	instance->autorelease();

	return instance;
}

TaserRod::TaserRod() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 16, 20, ItemStats(
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
	0.15f
))
{
}

TaserRod::~TaserRod()
{
}

Item* TaserRod::clone()
{
	return TaserRod::create();
}

const std::string& TaserRod::getItemName()
{
	return TaserRod::SaveKey;
}

LocalizedString* TaserRod::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_TaserRod::create();
}

const std::string& TaserRod::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_TaserRod;
}

const std::string& TaserRod::getIdentifier()
{
	return TaserRod::SaveKey;
}

Vec2 TaserRod::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* TaserRod::getRecipe()
{
	return TaserRodPlans::create();
}
