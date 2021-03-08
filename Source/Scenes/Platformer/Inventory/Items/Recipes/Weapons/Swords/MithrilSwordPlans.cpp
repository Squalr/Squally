#include "MithrilSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilSwordPlans::SaveKey = "mithril-sword-plans";

MithrilSwordPlans* MithrilSwordPlans::create()
{
	MithrilSwordPlans* instance = new MithrilSwordPlans();

	instance->autorelease();

	return instance;
}

MithrilSwordPlans::MithrilSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

MithrilSwordPlans::~MithrilSwordPlans()
{
}

std::vector<Item*> MithrilSwordPlans::craft()
{
	return { MithrilSword::create() };
}

std::vector<std::tuple<Item*, int>> MithrilSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* MithrilSwordPlans::clone()
{
	return MithrilSwordPlans::create();
}

const std::string& MithrilSwordPlans::getItemName()
{
	return MithrilSwordPlans::SaveKey;
}

LocalizedString* MithrilSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_MithrilSword::create();
}

const std::string& MithrilSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MithrilSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_MithrilSword;
}

const std::string& MithrilSwordPlans::getIdentifier()
{
	return MithrilSwordPlans::SaveKey;
}
