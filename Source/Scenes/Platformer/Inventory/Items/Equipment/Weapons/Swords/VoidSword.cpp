#include "VoidSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/VoidSwordPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidSword::SaveKey = "void-sword";

VoidSword* VoidSword::create()
{
	VoidSword* instance = new VoidSword();

	instance->autorelease();

	return instance;
}

VoidSword::VoidSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 8, 11, ItemStats(
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

VoidSword::~VoidSword()
{
}

Item* VoidSword::clone()
{
	return VoidSword::create();
}

const std::string& VoidSword::getItemName()
{
	return VoidSword::SaveKey;
}

LocalizedString* VoidSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_VoidSword::create();
}

const std::string& VoidSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_VoidSword;
}

const std::string& VoidSword::getSerializationKey()
{
	return VoidSword::SaveKey;
}

Recipe* VoidSword::getRecipe()
{
	return VoidSwordPlans::create();
}
