#include "BarbedHelmPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BarbedHelmPlans::SaveKey = "barbed-helm-plans";

BarbedHelmPlans* BarbedHelmPlans::create()
{
	BarbedHelmPlans* instance = new BarbedHelmPlans();

	instance->autorelease();

	return instance;
}

BarbedHelmPlans::BarbedHelmPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BarbedHelmPlans::~BarbedHelmPlans()
{
}

std::vector<Item*> BarbedHelmPlans::craft()
{
	return { BarbedHelm::create() };
}

std::vector<std::tuple<Item*, int>> BarbedHelmPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* BarbedHelmPlans::clone()
{
	return BarbedHelmPlans::create();
}

LocalizedString* BarbedHelmPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_BarbedHelm::create();
}

const std::string& BarbedHelmPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string BarbedHelmPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_BarbedHelm;
}

const std::string& BarbedHelmPlans::getIdentifier()
{
	return BarbedHelmPlans::SaveKey;
}
