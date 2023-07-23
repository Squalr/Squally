#include "SilverWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SilverWandPlans::SaveKey = "golden-wand-plans";

SilverWandPlans* SilverWandPlans::create()
{
	SilverWandPlans* instance = new SilverWandPlans();

	instance->autorelease();

	return instance;
}

SilverWandPlans::SilverWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SilverWandPlans::~SilverWandPlans()
{
}

std::vector<Item*> SilverWandPlans::craft()
{
	return { SilverWand::create() };
}

std::vector<std::tuple<Item*, int>> SilverWandPlans::getReagentsInternal()
{
	return
	{
		{ Silver::create(), 3 },
		{ Iron::create(), 2 },
		{ Coal::create(), 3 },
	};
}

Item* SilverWandPlans::clone()
{
	return SilverWandPlans::create();
}

LocalizedString* SilverWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_SilverWand::create();
}

const std::string& SilverWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SilverWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_SilverWand;
}

const std::string& SilverWandPlans::getIdentifier()
{
	return SilverWandPlans::SaveKey;
}
