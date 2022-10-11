#include "TurbanPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TurbanPlans::SaveKey = "turban-plans";

TurbanPlans* TurbanPlans::create()
{
	TurbanPlans* instance = new TurbanPlans();

	instance->autorelease();

	return instance;
}

TurbanPlans::TurbanPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TurbanPlans::~TurbanPlans()
{
}

std::vector<Item*> TurbanPlans::craft()
{
	return { Turban::create() };
}

std::vector<std::tuple<Item*, int>> TurbanPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* TurbanPlans::clone()
{
	return TurbanPlans::create();
}

LocalizedString* TurbanPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_Turban::create();
}

const std::string& TurbanPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TurbanPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Turban;
}

const std::string& TurbanPlans::getIdentifier()
{
	return TurbanPlans::SaveKey;
}
