#include "Timmy.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/TimmyPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Timmy::SaveKey = "timmy";

Timmy* Timmy::create()
{
	Timmy* instance = new Timmy();

	instance->autorelease();

	return instance;
}

Timmy::Timmy() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
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

Timmy::~Timmy()
{
}

Item* Timmy::clone()
{
	return Timmy::create();
}

std::string Timmy::getItemName()
{
	return Timmy::SaveKey;
}

LocalizedString* Timmy::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_Timmy::create();
}

std::string Timmy::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_Timmy;
}

std::string Timmy::getSerializationKey()
{
	return Timmy::SaveKey;
}

Vec2 Timmy::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* Timmy::getRecipe()
{
	return TimmyPlans::create();
}
