#include "ChieftainsWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ChieftainsWandPlans::SaveKey = "chieftains-wand-plans";

ChieftainsWandPlans* ChieftainsWandPlans::create()
{
	ChieftainsWandPlans* instance = new ChieftainsWandPlans();

	instance->autorelease();

	return instance;
}

ChieftainsWandPlans::ChieftainsWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

ChieftainsWandPlans::~ChieftainsWandPlans()
{
}

std::vector<Item*> ChieftainsWandPlans::craft()
{
	return { ChieftainsWand::create() };
}

std::vector<std::tuple<Item*, int>> ChieftainsWandPlans::getReagentsInternal()
{
	return
	{
		{ DarkWood::create(), 2 },
		{ Sulfur::create(), 4 },
	};
}

Item* ChieftainsWandPlans::clone()
{
	return ChieftainsWandPlans::create();
}

LocalizedString* ChieftainsWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_ChieftainsWand::create();
}

const std::string& ChieftainsWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string ChieftainsWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Special_ChieftainsWand;
}

const std::string& ChieftainsWandPlans::getIdentifier()
{
	return ChieftainsWandPlans::SaveKey;
}
