#include "CandySword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/CandySwordPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CandySword::SaveKey = "candy-sword";

CandySword* CandySword::create()
{
	CandySword* instance = new CandySword();

	instance->autorelease();

	return instance;
}

CandySword::CandySword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 32, 40, ItemStats(
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

CandySword::~CandySword()
{
}

Item* CandySword::clone()
{
	return CandySword::create();
}

LocalizedString* CandySword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_CandySword::create();
}

const std::string& CandySword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_CandySword;
}

const std::string& CandySword::getIdentifier()
{
	return CandySword::SaveKey;
}

Recipe* CandySword::getRecipe()
{
	return CandySwordPlans::create();
}
