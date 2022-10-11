#include "ConchHelmPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ConchHelmPlans::SaveKey = "conch-helm-plans";

ConchHelmPlans* ConchHelmPlans::create()
{
	ConchHelmPlans* instance = new ConchHelmPlans();

	instance->autorelease();

	return instance;
}

ConchHelmPlans::ConchHelmPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

ConchHelmPlans::~ConchHelmPlans()
{
}

std::vector<Item*> ConchHelmPlans::craft()
{
	return { ConchHelm::create() };
}

std::vector<std::tuple<Item*, int>> ConchHelmPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* ConchHelmPlans::clone()
{
	return ConchHelmPlans::create();
}

LocalizedString* ConchHelmPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_ConchHelm::create();
}

const std::string& ConchHelmPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string ConchHelmPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_ConchHelm;
}

const std::string& ConchHelmPlans::getIdentifier()
{
	return ConchHelmPlans::SaveKey;
}
