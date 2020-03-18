#include "EmeraldWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EmeraldWand::SaveKeyEmeraldWand = "emerald-wand";

EmeraldWand* EmeraldWand::create()
{
	EmeraldWand* instance = new EmeraldWand();

	instance->autorelease();

	return instance;
}

EmeraldWand::EmeraldWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 28, ItemStats(
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

EmeraldWand::~EmeraldWand()
{
}

Item* EmeraldWand::clone()
{
	return EmeraldWand::create();
}

std::string EmeraldWand::getItemName()
{
	return EmeraldWand::SaveKeyEmeraldWand;
}

LocalizedString* EmeraldWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_EmeraldWand::create();
}

std::string EmeraldWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_EmeraldWand;
}

std::string EmeraldWand::getSerializationKey()
{
	return EmeraldWand::SaveKeyEmeraldWand;
}

Vec2 EmeraldWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
