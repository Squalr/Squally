#include "DreadmournPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DreadmournPlans::SaveKey = "dread-mourn-plans";

DreadmournPlans* DreadmournPlans::create()
{
	DreadmournPlans* instance = new DreadmournPlans();

	instance->autorelease();

	return instance;
}

DreadmournPlans::DreadmournPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DreadmournPlans::~DreadmournPlans()
{
}

std::vector<Item*> DreadmournPlans::craft()
{
	return { Dreadmourn::create() };
}

std::vector<std::tuple<Item*, int>> DreadmournPlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 8 },
		{ Coal::create(), 4 },
		{ Gold::create(), 2 },
		{ Emerald::create(), 1 },
	};
}

Item* DreadmournPlans::clone()
{
	return DreadmournPlans::create();
}

const std::string& DreadmournPlans::getItemName()
{
	return DreadmournPlans::SaveKey;
}

LocalizedString* DreadmournPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Dreadmourn::create();
}

const std::string& DreadmournPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DreadmournPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Special_Dreadmourn;
}

const std::string& DreadmournPlans::getIdentifier()
{
	return DreadmournPlans::SaveKey;
}
