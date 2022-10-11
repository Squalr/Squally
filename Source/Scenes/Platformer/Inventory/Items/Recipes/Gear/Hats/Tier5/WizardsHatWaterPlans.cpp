#include "WizardsHatWaterPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatWaterPlans::SaveKey = "wizards-hat-water-plans";

WizardsHatWaterPlans* WizardsHatWaterPlans::create()
{
	WizardsHatWaterPlans* instance = new WizardsHatWaterPlans();

	instance->autorelease();

	return instance;
}

WizardsHatWaterPlans::WizardsHatWaterPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WizardsHatWaterPlans::~WizardsHatWaterPlans()
{
}

std::vector<Item*> WizardsHatWaterPlans::craft()
{
	return { WizardsHatWater::create() };
}

std::vector<std::tuple<Item*, int>> WizardsHatWaterPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WizardsHatWaterPlans::clone()
{
	return WizardsHatWaterPlans::create();
}

LocalizedString* WizardsHatWaterPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatWater::create();
}

const std::string& WizardsHatWaterPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WizardsHatWaterPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WizardsHatWater;
}

const std::string& WizardsHatWaterPlans::getIdentifier()
{
	return WizardsHatWaterPlans::SaveKey;
}
