#include "MithrilSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilSwordPlans::SaveKeyMithrilSwordPlans = "mithril-sword-plans";

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

Item* MithrilSwordPlans::craft()
{
	return MithrilSword::create();
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

std::string MithrilSwordPlans::getItemName()
{
	return MithrilSwordPlans::SaveKeyMithrilSwordPlans;
}

LocalizedString* MithrilSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_MithrilSword::create();
}

std::string MithrilSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MithrilSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_MithrilSword;
}

std::string MithrilSwordPlans::getSerializationKey()
{
	return MithrilSwordPlans::SaveKeyMithrilSwordPlans;
}
