#include "CopperMallet.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/CopperMalletPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperMallet::SaveKey = "copper-mallet";

CopperMallet* CopperMallet::create()
{
	CopperMallet* instance = new CopperMallet();

	instance->autorelease();

	return instance;
}

CopperMallet::CopperMallet() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 7, 9, ItemStats(
	// Health
	3,
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

CopperMallet::~CopperMallet()
{
}

Item* CopperMallet::clone()
{
	return CopperMallet::create();
}

std::string CopperMallet::getItemName()
{
	return CopperMallet::SaveKey;
}

LocalizedString* CopperMallet::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_CopperMallet::create();
}

std::string CopperMallet::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_CopperMallet;
}

std::string CopperMallet::getSerializationKey()
{
	return CopperMallet::SaveKey;
}

Vec2 CopperMallet::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* CopperMallet::getRecipe()
{
	return CopperMalletPlans::create();
}
