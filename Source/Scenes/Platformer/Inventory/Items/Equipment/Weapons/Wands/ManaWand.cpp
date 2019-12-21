#include "ManaWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ManaWand::SaveKeyManaWand = "mana-wand";

ManaWand* ManaWand::create()
{
	ManaWand* instance = new ManaWand();

	instance->autorelease();

	return instance;
}

ManaWand::ManaWand() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6, ItemStats(
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

ManaWand::~ManaWand()
{
}

Item* ManaWand::clone()
{
	return ManaWand::create();
}

std::string ManaWand::getItemName()
{
	return ManaWand::SaveKeyManaWand;
}

LocalizedString* ManaWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_ManaWand::create();
}

std::string ManaWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_ManaWand;
}

std::string ManaWand::getSerializationKey()
{
	return ManaWand::SaveKeyManaWand;
}

Vec2 ManaWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
