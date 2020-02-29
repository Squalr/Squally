#include "BattleAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
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

BattleAxePlans::BattleAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BattleAxePlans::~BattleAxePlans()
{
}

Item* BattleAxePlans::craft()
{
	return BattleAxe::create();
}

std::map<Item*, int> BattleAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
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
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string BattleAxePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_BattleAxe;
}

std::string BattleAxePlans::getSerializationKey()
{
	return BattleAxePlans::SaveKeyBattleAxePlans;
}
