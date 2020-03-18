#include "TheButcherPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheButcherPlans::SaveKeyTheButcherPlans = "the-butcher-plans";

TheButcherPlans* TheButcherPlans::create()
{
	TheButcherPlans* instance = new TheButcherPlans();

	instance->autorelease();

	return instance;
}

TheButcherPlans::TheButcherPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TheButcherPlans::~TheButcherPlans()
{
}

Item* TheButcherPlans::craft()
{
	return TheButcher::create();
}

std::vector<std::tuple<Item*, int>> TheButcherPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 1 },
		{ Iron::create(), 10 },
	};
}

Item* TheButcherPlans::clone()
{
	return TheButcherPlans::create();
}

std::string TheButcherPlans::getItemName()
{
	return TheButcherPlans::SaveKeyTheButcherPlans;
}

LocalizedString* TheButcherPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_TheButcher::create();
}

std::string TheButcherPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TheButcherPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_TheButcher;
}

std::string TheButcherPlans::getSerializationKey()
{
	return TheButcherPlans::SaveKeyTheButcherPlans;
}
