#include "BattleAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BattleAxe::SaveKeyBattleAxe = "battle-axe";

BattleAxe* BattleAxe::create()
{
	BattleAxe* instance = new BattleAxe();

	instance->autorelease();

	return instance;
}

BattleAxe::BattleAxe() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 4, 7, ItemStats(
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

BattleAxe::~BattleAxe()
{
}

Item* BattleAxe::clone()
{
	return BattleAxe::create();
}

std::string BattleAxe::getItemName()
{
	return BattleAxe::SaveKeyBattleAxe;
}

LocalizedString* BattleAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_BattleAxe::create();
}

std::string BattleAxe::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_BattleAxe;
}

std::string BattleAxe::getSerializationKey()
{
	return BattleAxe::SaveKeyBattleAxe;
}

Size BattleAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 BattleAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
