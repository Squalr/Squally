#include "WizardsHatShadowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatShadowPlans::SaveKey = "wizards-hat-shadow-plans";

WizardsHatShadowPlans* WizardsHatShadowPlans::create()
{
	WizardsHatShadowPlans* instance = new WizardsHatShadowPlans();

	instance->autorelease();

	return instance;
}

WizardsHatShadowPlans::WizardsHatShadowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WizardsHatShadowPlans::~WizardsHatShadowPlans()
{
}

std::vector<Item*> WizardsHatShadowPlans::craft()
{
	return { WizardsHatShadow::create() };
}

std::vector<std::tuple<Item*, int>> WizardsHatShadowPlans::getReagentsInternal()
{
	return
	{
		{ Sulfur::create(), 2 },
		{ DemonRoot::create(), 2 },
		{ BlackBlood::create(), 2 },
	};
}

Item* WizardsHatShadowPlans::clone()
{
	return WizardsHatShadowPlans::create();
}

LocalizedString* WizardsHatShadowPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatShadow::create();
}

const std::string& WizardsHatShadowPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WizardsHatShadowPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier6_WizardsHatShadow;
}

const std::string& WizardsHatShadowPlans::getIdentifier()
{
	return WizardsHatShadowPlans::SaveKey;
}
