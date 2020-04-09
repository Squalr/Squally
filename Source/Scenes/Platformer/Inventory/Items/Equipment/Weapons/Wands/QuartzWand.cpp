#include "QuartzWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string QuartzWand::SaveKey = "mana-wand";

QuartzWand* QuartzWand::create()
{
	QuartzWand* instance = new QuartzWand();

	instance->autorelease();

	return instance;
}

// TODO: revert to lower damage once weapon skills are added.
QuartzWand::QuartzWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 6, 8, ItemStats(
	// Health
	0,
	// Mana
	8,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.15f
))
{
}

QuartzWand::~QuartzWand()
{
}

Item* QuartzWand::clone()
{
	return QuartzWand::create();
}

std::string QuartzWand::getItemName()
{
	return QuartzWand::SaveKey;
}

LocalizedString* QuartzWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_QuartzWand::create();
}

std::string QuartzWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_QuartzWand;
}

std::string QuartzWand::getSerializationKey()
{
	return QuartzWand::SaveKey;
}

Vec2 QuartzWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
