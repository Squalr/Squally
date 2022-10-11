#include "WoodenPikeHelmPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenPikeHelmPlans::SaveKey = "wooden-pike-plans";

WoodenPikeHelmPlans* WoodenPikeHelmPlans::create()
{
	WoodenPikeHelmPlans* instance = new WoodenPikeHelmPlans();

	instance->autorelease();

	return instance;
}

WoodenPikeHelmPlans::WoodenPikeHelmPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WoodenPikeHelmPlans::~WoodenPikeHelmPlans()
{
}

std::vector<Item*> WoodenPikeHelmPlans::craft()
{
	return { WoodenPikeHelm::create() };
}

std::vector<std::tuple<Item*, int>> WoodenPikeHelmPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WoodenPikeHelmPlans::clone()
{
	return WoodenPikeHelmPlans::create();
}

LocalizedString* WoodenPikeHelmPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WoodenPikeHelm::create();
}

const std::string& WoodenPikeHelmPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WoodenPikeHelmPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WoodenPikeHelm;
}

const std::string& WoodenPikeHelmPlans::getIdentifier()
{
	return WoodenPikeHelmPlans::SaveKey;
}
