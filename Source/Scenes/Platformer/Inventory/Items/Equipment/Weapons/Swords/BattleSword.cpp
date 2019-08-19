#include "BattleSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Swords/BattleSword.h"

using namespace cocos2d;

const std::string BattleSword::SaveKeyBattleSword = "battle-sword";

BattleSword* BattleSword::create()
{
	BattleSword* instance = new BattleSword();

	instance->autorelease();

	return instance;
}

BattleSword::BattleSword() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

BattleSword::~BattleSword()
{
}

Item* BattleSword::clone()
{
	return BattleSword::create();
}

std::string BattleSword::getItemName()
{
	return BattleSword::SaveKeyBattleSword;
}

LocalizedString* BattleSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_BattleSword::create();
}

std::string BattleSword::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_BattleSword;
}

std::string BattleSword::getSerializationKey()
{
	return BattleSword::SaveKeyBattleSword;
}
