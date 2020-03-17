#include "WoodCutterPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodCutterPlans::SaveKeyWoodCutterPlans = "wood-cutter-plans";

WoodCutterPlans* WoodCutterPlans::create()
{
	WoodCutterPlans* instance = new WoodCutterPlans();

	instance->autorelease();

	return instance;
}

WoodCutterPlans::WoodCutterPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WoodCutterPlans::~WoodCutterPlans()
{
}

Item* WoodCutterPlans::craft()
{
	return WoodCutter::create();
}

std::vector<std::tuple<Item*, int>> WoodCutterPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WoodCutterPlans::clone()
{
	return WoodCutterPlans::create();
}

std::string WoodCutterPlans::getItemName()
{
	return WoodCutterPlans::SaveKeyWoodCutterPlans;
}

LocalizedString* WoodCutterPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_WoodCutter::create();
}

std::string WoodCutterPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WoodCutterPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_WoodCutter;
}

std::string WoodCutterPlans::getSerializationKey()
{
	return WoodCutterPlans::SaveKeyWoodCutterPlans;
}
