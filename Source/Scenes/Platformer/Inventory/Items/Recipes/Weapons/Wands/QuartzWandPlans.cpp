#include "QuartzWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string QuartzWandPlans::SaveKey = "quartz-wand-plans";

QuartzWandPlans* QuartzWandPlans::create()
{
	QuartzWandPlans* instance = new QuartzWandPlans();

	instance->autorelease();

	return instance;
}

QuartzWandPlans::QuartzWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

QuartzWandPlans::~QuartzWandPlans()
{
}

std::vector<Item*> QuartzWandPlans::craft()
{
	return { QuartzWand::create() };
}

std::vector<std::tuple<Item*, int>> QuartzWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
		{ Quartz::create(), 2 },
	};
}

Item* QuartzWandPlans::clone()
{
	return QuartzWandPlans::create();
}

std::string QuartzWandPlans::getItemName()
{
	return QuartzWandPlans::SaveKey;
}

LocalizedString* QuartzWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_QuartzWand::create();
}

std::string QuartzWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string QuartzWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_QuartzWand;
}

std::string QuartzWandPlans::getSerializationKey()
{
	return QuartzWandPlans::SaveKey;
}
