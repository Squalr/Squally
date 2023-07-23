#include "DemonicSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonicSwordPlans::SaveKey = "demonic-sword-plans";

DemonicSwordPlans* DemonicSwordPlans::create()
{
	DemonicSwordPlans* instance = new DemonicSwordPlans();

	instance->autorelease();

	return instance;
}

DemonicSwordPlans::DemonicSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DemonicSwordPlans::~DemonicSwordPlans()
{
}

std::vector<Item*> DemonicSwordPlans::craft()
{
	return { DemonicSword::create() };
}

std::vector<std::tuple<Item*, int>> DemonicSwordPlans::getReagentsInternal()
{
	return
	{
		{ Ruby::create(), 1 },
		{ Sulfur::create(), 4},
		{ Iron::create(), 4 },
		{ Coal::create(), 4 },
	};
}

Item* DemonicSwordPlans::clone()
{
	return DemonicSwordPlans::create();
}

LocalizedString* DemonicSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_DemonicSword::create();
}

const std::string& DemonicSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DemonicSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_DemonicSword;
}

const std::string& DemonicSwordPlans::getIdentifier()
{
	return DemonicSwordPlans::SaveKey;
}
