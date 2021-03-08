#include "CopperSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/CopperSwordPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperSword::SaveKey = "copper-sword";

CopperSword* CopperSword::create()
{
	CopperSword* instance = new CopperSword();

	instance->autorelease();

	return instance;
}

CopperSword::CopperSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), 6, 9, ItemStats(
	// Health
	2,
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

CopperSword::~CopperSword()
{
}

Item* CopperSword::clone()
{
	return CopperSword::create();
}

LocalizedString* CopperSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_CopperSword::create();
}

const std::string& CopperSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_CopperSword;
}

const std::string& CopperSword::getIdentifier()
{
	return CopperSword::SaveKey;
}

Recipe* CopperSword::getRecipe()
{
	return CopperSwordPlans::create();
}
