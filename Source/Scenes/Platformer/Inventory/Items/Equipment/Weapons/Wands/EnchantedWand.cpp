#include "EnchantedWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EnchantedWand::SaveKeyEnchantedWand = "enchanted-wand";

EnchantedWand* EnchantedWand::create()
{
	EnchantedWand* instance = new EnchantedWand();

	instance->autorelease();

	return instance;
}

EnchantedWand::EnchantedWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 6, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

EnchantedWand::~EnchantedWand()
{
}

Item* EnchantedWand::clone()
{
	return EnchantedWand::create();
}

std::string EnchantedWand::getItemName()
{
	return EnchantedWand::SaveKeyEnchantedWand;
}

LocalizedString* EnchantedWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_EnchantedWand::create();
}

std::string EnchantedWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_EnchantedWand;
}

std::string EnchantedWand::getSerializationKey()
{
	return EnchantedWand::SaveKeyEnchantedWand;
}

Vec2 EnchantedWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
