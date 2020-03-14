#include "BattleHammerPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BattleHammerPlans::SaveKeyBattleHammerPlans = "battle-hammer-plans";

BattleHammerPlans* BattleHammerPlans::create()
{
	BattleHammerPlans* instance = new BattleHammerPlans();

	instance->autorelease();

	return instance;
}

BattleHammerPlans::BattleHammerPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BattleHammerPlans::~BattleHammerPlans()
{
}

Item* BattleHammerPlans::craft()
{
	return BattleHammer::create();
}

std::vector<std::tuple<Item*, int>> BattleHammerPlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 8 },
		{ Coal::create(), 8 },
		{ Copper::create(), 8 },
		{ Silver::create(), 2 },
		{ Sulfur::create(), 6 },
	};
}

Item* BattleHammerPlans::clone()
{
	return BattleHammerPlans::create();
}

std::string BattleHammerPlans::getItemName()
{
	return BattleHammerPlans::SaveKeyBattleHammerPlans;
}

LocalizedString* BattleHammerPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_BattleHammer::create();
}

std::string BattleHammerPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string BattleHammerPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_BattleHammer;
}

std::string BattleHammerPlans::getSerializationKey()
{
	return BattleHammerPlans::SaveKeyBattleHammerPlans;
}
