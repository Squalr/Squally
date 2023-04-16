#include "DemonHeartPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonHeartPlans::SaveKey = "hell-crystal-plans";

DemonHeartPlans* DemonHeartPlans::create()
{
	DemonHeartPlans* instance = new DemonHeartPlans();

	instance->autorelease();

	return instance;
}

DemonHeartPlans::DemonHeartPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DemonHeartPlans::~DemonHeartPlans()
{
}

std::vector<Item*> DemonHeartPlans::craft()
{
	return { HellKey::create() };
}

std::vector<std::tuple<Item*, int>> DemonHeartPlans::getReagentsInternal()
{
	return
	{
		{ DemonHeart::create(), 1 },
	};
}

Item* DemonHeartPlans::clone()
{
	return DemonHeartPlans::create();
}

LocalizedString* DemonHeartPlans::getString()
{
	return Strings::Items_Misc_Keys_DemonHeart::create();
}

const std::string& DemonHeartPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DemonHeartPlans::getCraftedItemIconResource()
{
	return ItemResources::Keys_DemonHeart;
}

const std::string& DemonHeartPlans::getIdentifier()
{
	return DemonHeartPlans::SaveKey;
}
