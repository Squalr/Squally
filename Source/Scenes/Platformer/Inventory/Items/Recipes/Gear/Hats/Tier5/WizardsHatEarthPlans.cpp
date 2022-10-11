#include "WizardsHatEarthPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatEarthPlans::SaveKey = "wizards-hat-earth-plans";

WizardsHatEarthPlans* WizardsHatEarthPlans::create()
{
	WizardsHatEarthPlans* instance = new WizardsHatEarthPlans();

	instance->autorelease();

	return instance;
}

WizardsHatEarthPlans::WizardsHatEarthPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WizardsHatEarthPlans::~WizardsHatEarthPlans()
{
}

std::vector<Item*> WizardsHatEarthPlans::craft()
{
	return { WizardsHatEarth::create() };
}

std::vector<std::tuple<Item*, int>> WizardsHatEarthPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WizardsHatEarthPlans::clone()
{
	return WizardsHatEarthPlans::create();
}

LocalizedString* WizardsHatEarthPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatEarth::create();
}

const std::string& WizardsHatEarthPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WizardsHatEarthPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WizardsHatEarth;
}

const std::string& WizardsHatEarthPlans::getIdentifier()
{
	return WizardsHatEarthPlans::SaveKey;
}
