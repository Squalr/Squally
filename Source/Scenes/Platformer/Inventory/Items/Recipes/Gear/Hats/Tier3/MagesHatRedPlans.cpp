#include "MagesHatRedPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MagesHatRedPlans::SaveKey = "mages-hat-red-plans";

MagesHatRedPlans* MagesHatRedPlans::create()
{
	MagesHatRedPlans* instance = new MagesHatRedPlans();

	instance->autorelease();

	return instance;
}

MagesHatRedPlans::MagesHatRedPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

MagesHatRedPlans::~MagesHatRedPlans()
{
}

std::vector<Item*> MagesHatRedPlans::craft()
{
	return { MagesHatRed::create() };
}

std::vector<std::tuple<Item*, int>> MagesHatRedPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* MagesHatRedPlans::clone()
{
	return MagesHatRedPlans::create();
}

LocalizedString* MagesHatRedPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_MagesHatRed::create();
}

const std::string& MagesHatRedPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MagesHatRedPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_MagesHatRed;
}

const std::string& MagesHatRedPlans::getIdentifier()
{
	return MagesHatRedPlans::SaveKey;
}
