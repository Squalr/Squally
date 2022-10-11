#include "TaserRodPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TaserRodPlans::SaveKey = "taser-rod-plans";

TaserRodPlans* TaserRodPlans::create()
{
	TaserRodPlans* instance = new TaserRodPlans();

	instance->autorelease();

	return instance;
}

TaserRodPlans::TaserRodPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TaserRodPlans::~TaserRodPlans()
{
}

std::vector<Item*> TaserRodPlans::craft()
{
	return { TaserRod::create() };
}

std::vector<std::tuple<Item*, int>> TaserRodPlans::getReagentsInternal()
{
	return
	{
		{ Sapphire::create(), 4 },
		{ Sulfur::create(), 1 },
	};
}

Item* TaserRodPlans::clone()
{
	return TaserRodPlans::create();
}

LocalizedString* TaserRodPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_TaserRod::create();
}

const std::string& TaserRodPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TaserRodPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Special_TaserRod;
}

const std::string& TaserRodPlans::getIdentifier()
{
	return TaserRodPlans::SaveKey;
}
