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
		{ Iron::create(), 8 },
		{ Coal::create(), 4 },
		{ Gold::create(), 2 },
	};
}

Item* DemonicSwordPlans::clone()
{
	return DemonicSwordPlans::create();
}

std::string DemonicSwordPlans::getItemName()
{
	return DemonicSwordPlans::SaveKey;
}

LocalizedString* DemonicSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_DemonicSword::create();
}

std::string DemonicSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DemonicSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_DemonicSword;
}

std::string DemonicSwordPlans::getSerializationKey()
{
	return DemonicSwordPlans::SaveKey;
}
