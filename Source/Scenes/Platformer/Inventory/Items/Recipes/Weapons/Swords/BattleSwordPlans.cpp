#include "BattleSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BattleSwordPlans::SaveKeyBattleSwordPlans = "battle-sword-plans";

BattleSwordPlans* BattleSwordPlans::create()
{
	BattleSwordPlans* instance = new BattleSwordPlans();

	instance->autorelease();

	return instance;
}

BattleSwordPlans::BattleSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BattleSwordPlans::~BattleSwordPlans()
{
}

Item* BattleSwordPlans::craft()
{
	return BattleSword::create();
}

std::map<Item*, int> BattleSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* BattleSwordPlans::clone()
{
	return BattleSwordPlans::create();
}

std::string BattleSwordPlans::getItemName()
{
	return BattleSwordPlans::SaveKeyBattleSwordPlans;
}

LocalizedString* BattleSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_BattleSword::create();
}

std::string BattleSwordPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string BattleSwordPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_BattleSword;
}

std::string BattleSwordPlans::getSerializationKey()
{
	return BattleSwordPlans::SaveKeyBattleSwordPlans;
}
