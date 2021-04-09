#include "VikingHelmetPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VikingHelmetPlans::SaveKey = "viking-helmet-plans";

VikingHelmetPlans* VikingHelmetPlans::create()
{
	VikingHelmetPlans* instance = new VikingHelmetPlans();

	instance->autorelease();

	return instance;
}

VikingHelmetPlans::VikingHelmetPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

VikingHelmetPlans::~VikingHelmetPlans()
{
}

std::vector<Item*> VikingHelmetPlans::craft()
{
	return { VikingHelmet::create() };
}

std::vector<std::tuple<Item*, int>> VikingHelmetPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* VikingHelmetPlans::clone()
{
	return VikingHelmetPlans::create();
}

LocalizedString* VikingHelmetPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_VikingHelmet::create();
}

const std::string& VikingHelmetPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string VikingHelmetPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_VikingHelmet;
}

const std::string& VikingHelmetPlans::getIdentifier()
{
	return VikingHelmetPlans::SaveKey;
}
