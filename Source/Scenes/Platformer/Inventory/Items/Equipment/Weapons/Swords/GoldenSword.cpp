#include "GoldenSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/GoldenSwordPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenSword::SaveKey = "golden-sword";

GoldenSword* GoldenSword::create()
{
	GoldenSword* instance = new GoldenSword();

	instance->autorelease();

	return instance;
}

GoldenSword::GoldenSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 10, 13, ItemStats(
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

GoldenSword::~GoldenSword()
{
}

Item* GoldenSword::clone()
{
	return GoldenSword::create();
}

std::string GoldenSword::getItemName()
{
	return GoldenSword::SaveKey;
}

LocalizedString* GoldenSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_GoldenSword::create();
}

std::string GoldenSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_GoldenSword;
}

std::string GoldenSword::getSerializationKey()
{
	return GoldenSword::SaveKey;
}

Recipe* GoldenSword::getRecipe()
{
	return GoldenSwordPlans::create();
}
