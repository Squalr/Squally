#include "SteelHelmPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelHelmPlans::SaveKey = "steel-helm-plans";

SteelHelmPlans* SteelHelmPlans::create()
{
	SteelHelmPlans* instance = new SteelHelmPlans();

	instance->autorelease();

	return instance;
}

SteelHelmPlans::SteelHelmPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SteelHelmPlans::~SteelHelmPlans()
{
}

std::vector<Item*> SteelHelmPlans::craft()
{
	return { SteelHelm::create() };
}

std::vector<std::tuple<Item*, int>> SteelHelmPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* SteelHelmPlans::clone()
{
	return SteelHelmPlans::create();
}

LocalizedString* SteelHelmPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SteelHelm::create();
}

const std::string& SteelHelmPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SteelHelmPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_SteelHelm;
}

const std::string& SteelHelmPlans::getIdentifier()
{
	return SteelHelmPlans::SaveKey;
}
