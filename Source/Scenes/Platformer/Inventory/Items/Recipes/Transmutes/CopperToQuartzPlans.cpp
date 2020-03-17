#include "CopperToQuartzPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperToQuartzPlans::SaveKeyCopperToQuartzPlans = "copper-to-quartz-plans";

CopperToQuartzPlans* CopperToQuartzPlans::create()
{
	CopperToQuartzPlans* instance = new CopperToQuartzPlans();

	instance->autorelease();

	return instance;
}

CopperToQuartzPlans::CopperToQuartzPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CopperToQuartzPlans::~CopperToQuartzPlans()
{
}

Item* CopperToQuartzPlans::craft()
{
	return Quartz::create();
}

std::vector<std::tuple<Item*, int>> CopperToQuartzPlans::getReagentsInternal()
{
	return
	{
		{ Copper::create(), 2 },
	};
}

Item* CopperToQuartzPlans::clone()
{
	return CopperToQuartzPlans::create();
}

std::string CopperToQuartzPlans::getItemName()
{
	return CopperToQuartzPlans::SaveKeyCopperToQuartzPlans;
}

LocalizedString* CopperToQuartzPlans::getString()
{
	return Strings::Items_Crafting_Ore_Quartz::create();
}

std::string CopperToQuartzPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string CopperToQuartzPlans::getCraftedItemIconResource()
{
	return ItemResources::Crafting_Ores_Quartz;
}

std::string CopperToQuartzPlans::getSerializationKey()
{
	return CopperToQuartzPlans::SaveKeyCopperToQuartzPlans;
}
