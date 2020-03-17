#include "RendPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RendPlans::SaveKeyRendPlans = "rend-plans";

RendPlans* RendPlans::create()
{
	RendPlans* instance = new RendPlans();

	instance->autorelease();

	return instance;
}

RendPlans::RendPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

RendPlans::~RendPlans()
{
}

Item* RendPlans::craft()
{
	return Rend::create();
}

std::vector<std::tuple<Item*, int>> RendPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* RendPlans::clone()
{
	return RendPlans::create();
}

std::string RendPlans::getItemName()
{
	return RendPlans::SaveKeyRendPlans;
}

LocalizedString* RendPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_Rend::create();
}

std::string RendPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string RendPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_Rend;
}

std::string RendPlans::getSerializationKey()
{
	return RendPlans::SaveKeyRendPlans;
}
