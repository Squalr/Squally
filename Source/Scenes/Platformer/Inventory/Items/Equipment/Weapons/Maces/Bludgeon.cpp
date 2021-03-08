#include "Bludgeon.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/BludgeonPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Bludgeon::SaveKey = "bludgeon";

Bludgeon* Bludgeon::create()
{
	Bludgeon* instance = new Bludgeon();

	instance->autorelease();

	return instance;
}

Bludgeon::Bludgeon() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
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

Bludgeon::~Bludgeon()
{
}

Item* Bludgeon::clone()
{
	return Bludgeon::create();
}

LocalizedString* Bludgeon::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_Bludgeon::create();
}

const std::string& Bludgeon::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_Bludgeon;
}

const std::string& Bludgeon::getIdentifier()
{
	return Bludgeon::SaveKey;
}

Vec2 Bludgeon::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* Bludgeon::getRecipe()
{
	return BludgeonPlans::create();
}
