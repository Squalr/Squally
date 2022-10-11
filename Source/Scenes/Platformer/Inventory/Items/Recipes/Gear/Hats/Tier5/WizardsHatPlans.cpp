#include "WizardsHatPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatPlans::SaveKey = "wizards-hat-plans";

WizardsHatPlans* WizardsHatPlans::create()
{
	WizardsHatPlans* instance = new WizardsHatPlans();

	instance->autorelease();

	return instance;
}

WizardsHatPlans::WizardsHatPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WizardsHatPlans::~WizardsHatPlans()
{
}

std::vector<Item*> WizardsHatPlans::craft()
{
	return { WizardsHat::create() };
}

std::vector<std::tuple<Item*, int>> WizardsHatPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WizardsHatPlans::clone()
{
	return WizardsHatPlans::create();
}

LocalizedString* WizardsHatPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHat::create();
}

const std::string& WizardsHatPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WizardsHatPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WizardsHat;
}

const std::string& WizardsHatPlans::getIdentifier()
{
	return WizardsHatPlans::SaveKey;
}
