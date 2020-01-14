#include "BattleAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BattleAxePlans::SaveKeyBattleAxePlans = "battle-axe-plans";

BattleAxePlans* BattleAxePlans::create()
{
	BattleAxePlans* instance = new BattleAxePlans();

	instance->autorelease();

	return instance;
}

BattleAxePlans::BattleAxePlans() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), ItemMeta(1))
{
}

BattleAxePlans::~BattleAxePlans()
{
}

Item* BattleAxePlans::craft()
{
	return BattleAxe::create();
}

std::map<std::string, int> BattleAxePlans::getReagents()
{
	return
	{
		{ Wood::SaveKeyWood, 2 },
		{ Iron::SaveKeyIron, 4 },
	};
}

Item* BattleAxePlans::clone()
{
	return BattleAxePlans::create();
}

std::string BattleAxePlans::getItemName()
{
	return BattleAxePlans::SaveKeyBattleAxePlans;
}

LocalizedString* BattleAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_BattleAxe::create();
}

std::string BattleAxePlans::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_BattleAxe;
}

std::string BattleAxePlans::getSerializationKey()
{
	return BattleAxePlans::SaveKeyBattleAxePlans;
}
