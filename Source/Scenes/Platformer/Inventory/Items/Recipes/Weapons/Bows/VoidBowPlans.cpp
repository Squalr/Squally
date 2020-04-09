#include "VoidBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidBowPlans::SaveKey = "void-bow-plans";

VoidBowPlans* VoidBowPlans::create()
{
	VoidBowPlans* instance = new VoidBowPlans();

	instance->autorelease();

	return instance;
}

VoidBowPlans::VoidBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

VoidBowPlans::~VoidBowPlans()
{
}

Item* VoidBowPlans::craft()
{
	return VoidBow::create();
}

std::vector<std::tuple<Item*, int>> VoidBowPlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 10 },
		{ Coal::create(), 8 },
		{ Tin::create(), 4 },
	};
}

Item* VoidBowPlans::clone()
{
	return VoidBowPlans::create();
}

std::string VoidBowPlans::getItemName()
{
	return VoidBowPlans::SaveKey;
}

LocalizedString* VoidBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_VoidBow::create();
}

std::string VoidBowPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string VoidBowPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_VoidBow;
}

std::string VoidBowPlans::getSerializationKey()
{
	return VoidBowPlans::SaveKey;
}
