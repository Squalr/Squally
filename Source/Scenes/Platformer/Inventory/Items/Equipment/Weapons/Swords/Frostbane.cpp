#include "Frostbane.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/FrostbanePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Frostbane::SaveKey = "frost-bane";

Frostbane* Frostbane::create()
{
	Frostbane* instance = new Frostbane();

	instance->autorelease();

	return instance;
}

Frostbane::Frostbane() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
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

Frostbane::~Frostbane()
{
}

Item* Frostbane::clone()
{
	return Frostbane::create();
}

const std::string& Frostbane::getItemName()
{
	return Frostbane::SaveKey;
}

LocalizedString* Frostbane::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Frostbane::create();
}

const std::string& Frostbane::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_Frostbane;
}

const std::string& Frostbane::getIdentifier()
{
	return Frostbane::SaveKey;
}

Recipe* Frostbane::getRecipe()
{
	return FrostbanePlans::create();
}
