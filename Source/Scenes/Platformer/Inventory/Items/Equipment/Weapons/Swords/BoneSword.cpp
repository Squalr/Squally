#include "BoneSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/BoneSwordPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneSword::SaveKey = "bone-sword";

BoneSword* BoneSword::create()
{
	BoneSword* instance = new BoneSword();

	instance->autorelease();

	return instance;
}

BoneSword::BoneSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 10 }}), 8, 11, ItemStats(
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

BoneSword::~BoneSword()
{
}

Item* BoneSword::clone()
{
	return BoneSword::create();
}

LocalizedString* BoneSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_BoneSword::create();
}

const std::string& BoneSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_BoneSword;
}

const std::string& BoneSword::getIdentifier()
{
	return BoneSword::SaveKey;
}

Recipe* BoneSword::getRecipe()
{
	return BoneSwordPlans::create();
}
