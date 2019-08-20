#include "BattleHammer.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Maces/BattleHammer.h"

using namespace cocos2d;

const std::string BattleHammer::SaveKeyBattleHammer = "battle-hammer";

BattleHammer* BattleHammer::create()
{
	BattleHammer* instance = new BattleHammer();

	instance->autorelease();

	return instance;
}

BattleHammer::BattleHammer() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

BattleHammer::~BattleHammer()
{
}

Item* BattleHammer::clone()
{
	return BattleHammer::create();
}

std::string BattleHammer::getItemName()
{
	return BattleHammer::SaveKeyBattleHammer;
}

LocalizedString* BattleHammer::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_BattleHammer::create();
}

std::string BattleHammer::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_BattleHammer;
}

std::string BattleHammer::getSerializationKey()
{
	return BattleHammer::SaveKeyBattleHammer;
}

Vec2 BattleHammer::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
