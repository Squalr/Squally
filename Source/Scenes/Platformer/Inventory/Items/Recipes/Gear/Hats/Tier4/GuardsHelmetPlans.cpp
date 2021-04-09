#include "GuardsHelmetPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GuardsHelmetPlans::SaveKey = "guards-helmet-plans";

GuardsHelmetPlans* GuardsHelmetPlans::create()
{
	GuardsHelmetPlans* instance = new GuardsHelmetPlans();

	instance->autorelease();

	return instance;
}

GuardsHelmetPlans::GuardsHelmetPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GuardsHelmetPlans::~GuardsHelmetPlans()
{
}

std::vector<Item*> GuardsHelmetPlans::craft()
{
	return { GuardsHelmet::create() };
}

std::vector<std::tuple<Item*, int>> GuardsHelmetPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* GuardsHelmetPlans::clone()
{
	return GuardsHelmetPlans::create();
}

LocalizedString* GuardsHelmetPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_GuardsHelmet::create();
}

const std::string& GuardsHelmetPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GuardsHelmetPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_GuardsHelmet;
}

const std::string& GuardsHelmetPlans::getIdentifier()
{
	return GuardsHelmetPlans::SaveKey;
}
