#include "TheButcher.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/TheButcherPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheButcher::SaveKey = "the-butcher";

TheButcher* TheButcher::create()
{
	TheButcher* instance = new TheButcher();

	instance->autorelease();

	return instance;
}

TheButcher::TheButcher() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
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

TheButcher::~TheButcher()
{
}

Item* TheButcher::clone()
{
	return TheButcher::create();
}

LocalizedString* TheButcher::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_TheButcher::create();
}

const std::string& TheButcher::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_TheButcher;
}

const std::string& TheButcher::getIdentifier()
{
	return TheButcher::SaveKey;
}

Recipe* TheButcher::getRecipe()
{
	return TheButcherPlans::create();
}
