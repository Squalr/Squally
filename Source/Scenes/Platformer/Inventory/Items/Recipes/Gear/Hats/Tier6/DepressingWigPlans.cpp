#include "DepressingWigPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DepressingWigPlans::SaveKey = "depressing-wig-plans";

DepressingWigPlans* DepressingWigPlans::create()
{
	DepressingWigPlans* instance = new DepressingWigPlans();

	instance->autorelease();

	return instance;
}

DepressingWigPlans::DepressingWigPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DepressingWigPlans::~DepressingWigPlans()
{
}

std::vector<Item*> DepressingWigPlans::craft()
{
	return { DepressingWig::create() };
}

std::vector<std::tuple<Item*, int>> DepressingWigPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* DepressingWigPlans::clone()
{
	return DepressingWigPlans::create();
}

LocalizedString* DepressingWigPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_DepressingWig::create();
}

const std::string& DepressingWigPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DepressingWigPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_DepressingWig;
}

const std::string& DepressingWigPlans::getIdentifier()
{
	return DepressingWigPlans::SaveKey;
}
