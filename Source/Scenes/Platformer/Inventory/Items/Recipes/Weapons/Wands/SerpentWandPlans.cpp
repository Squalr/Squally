#include "SerpentWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SerpentWandPlans::SaveKey = "serpent-wand-plans";

SerpentWandPlans* SerpentWandPlans::create()
{
	SerpentWandPlans* instance = new SerpentWandPlans();

	instance->autorelease();

	return instance;
}

SerpentWandPlans::SerpentWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SerpentWandPlans::~SerpentWandPlans()
{
}

std::vector<Item*> SerpentWandPlans::craft()
{
	return { TaserRod::create() };
}

std::vector<std::tuple<Item*, int>> SerpentWandPlans::getReagentsInternal()
{
	return
	{
		{ Sapphire::create(), 4 },
		{ Sulfur::create(), 1 },
	};
}

Item* SerpentWandPlans::clone()
{
	return SerpentWandPlans::create();
}

const std::string& SerpentWandPlans::getItemName()
{
	return SerpentWandPlans::SaveKey;
}

LocalizedString* SerpentWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_TaserRod::create();
}

const std::string& SerpentWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SerpentWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Special_TaserRod;
}

const std::string& SerpentWandPlans::getIdentifier()
{
	return SerpentWandPlans::SaveKey;
}
