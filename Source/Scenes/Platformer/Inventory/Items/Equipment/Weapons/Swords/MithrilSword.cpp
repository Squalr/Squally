#include "MithrilSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/MithrilSwordPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilSword::SaveKey = "mithril-sword";

MithrilSword* MithrilSword::create()
{
	MithrilSword* instance = new MithrilSword();

	instance->autorelease();

	return instance;
}

MithrilSword::MithrilSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), SWORD_DAMAGE_MIN(5), SWORD_DAMAGE_MAX(5), ItemStats(
	// Health
	3,
	// Mana
	2,
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

MithrilSword::~MithrilSword()
{
}

Item* MithrilSword::clone()
{
	return MithrilSword::create();
}

LocalizedString* MithrilSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_MithrilSword::create();
}

const std::string& MithrilSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_MithrilSword;
}

const std::string& MithrilSword::getIdentifier()
{
	return MithrilSword::SaveKey;
}

Recipe* MithrilSword::getRecipe()
{
	return MithrilSwordPlans::create();
}
