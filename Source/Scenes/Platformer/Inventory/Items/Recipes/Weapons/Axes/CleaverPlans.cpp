#include "CleaverPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CleaverPlans::SaveKeyCleaverPlans = "blue-axe-plans";

CleaverPlans* CleaverPlans::create()
{
	CleaverPlans* instance = new CleaverPlans();

	instance->autorelease();

	return instance;
}

CleaverPlans::CleaverPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CleaverPlans::~CleaverPlans()
{
}

Item* CleaverPlans::craft()
{
	return Cleaver::create();
}

std::vector<std::tuple<Item*, int>> CleaverPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* CleaverPlans::clone()
{
	return CleaverPlans::create();
}

std::string CleaverPlans::getItemName()
{
	return CleaverPlans::SaveKeyCleaverPlans;
}

LocalizedString* CleaverPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_Cleaver::create();
}

std::string CleaverPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string CleaverPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_Cleaver;
}

std::string CleaverPlans::getSerializationKey()
{
	return CleaverPlans::SaveKeyCleaverPlans;
}
