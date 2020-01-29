#include "CursedWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CursedWand::SaveKeyCursedWand = "cursed-wand";

CursedWand* CursedWand::create()
{
	CursedWand* instance = new CursedWand();

	instance->autorelease();

	return instance;
}

CursedWand::CursedWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 3, 6, ItemStats(
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

CursedWand::~CursedWand()
{
}

Item* CursedWand::clone()
{
	return CursedWand::create();
}

std::string CursedWand::getItemName()
{
	return CursedWand::SaveKeyCursedWand;
}

LocalizedString* CursedWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_CursedWand::create();
}

std::string CursedWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_CursedWand;
}

std::string CursedWand::getSerializationKey()
{
	return CursedWand::SaveKeyCursedWand;
}

Vec2 CursedWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
