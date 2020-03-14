#include "HuntersBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HuntersBowPlans::SaveKeyHuntersBowPlans = "hunters-bow-plans";

HuntersBowPlans* HuntersBowPlans::create()
{
	HuntersBowPlans* instance = new HuntersBowPlans();

	instance->autorelease();

	return instance;
}

HuntersBowPlans::HuntersBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

HuntersBowPlans::~HuntersBowPlans()
{
}

Item* HuntersBowPlans::craft()
{
	return HuntersBow::create();
}

std::vector<std::tuple<Item*, int>> HuntersBowPlans::getReagentsInternal()
{
	return
	{
		{ LightWood::create(), 8 },
		{ Iron::create(), 2 },
	};
}

Item* HuntersBowPlans::clone()
{
	return HuntersBowPlans::create();
}

std::string HuntersBowPlans::getItemName()
{
	return HuntersBowPlans::SaveKeyHuntersBowPlans;
}

LocalizedString* HuntersBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_HuntersBow::create();
}

std::string HuntersBowPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string HuntersBowPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_HuntersBow;
}

std::string HuntersBowPlans::getSerializationKey()
{
	return HuntersBowPlans::SaveKeyHuntersBowPlans;
}
