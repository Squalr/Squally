#include "FireSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/FireSwordPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FireSword::SaveKey = "fire-sword";

FireSword* FireSword::create()
{
	FireSword* instance = new FireSword();

	instance->autorelease();

	return instance;
}

FireSword::FireSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 11, 15, ItemStats(
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

FireSword::~FireSword()
{
}

Item* FireSword::clone()
{
	return FireSword::create();
}

LocalizedString* FireSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_FireSword::create();
}

const std::string& FireSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_FireSword;
}

const std::string& FireSword::getIdentifier()
{
	return FireSword::SaveKey;
}

Recipe* FireSword::getRecipe()
{
	return FireSwordPlans::create();
}
