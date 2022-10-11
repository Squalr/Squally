#include "TigersBanePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TigersBanePlans::SaveKey = "tigers-bane-plans";

TigersBanePlans* TigersBanePlans::create()
{
	TigersBanePlans* instance = new TigersBanePlans();

	instance->autorelease();

	return instance;
}

TigersBanePlans::TigersBanePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TigersBanePlans::~TigersBanePlans()
{
}

std::vector<Item*> TigersBanePlans::craft()
{
	return { TigersBane::create() };
}

std::vector<std::tuple<Item*, int>> TigersBanePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* TigersBanePlans::clone()
{
	return TigersBanePlans::create();
}

LocalizedString* TigersBanePlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_TigersBane::create();
}

const std::string& TigersBanePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TigersBanePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_TigersBane;
}

const std::string& TigersBanePlans::getIdentifier()
{
	return TigersBanePlans::SaveKey;
}
