#include "TaserRodPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TaserRodPlans::SaveKeyTaserRodPlans = "taser-rod-plans";

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

Item* TaserRodPlans::craft()
{
	return TaserRod::create();
}

std::vector<std::tuple<Item*, int>> TaserRodPlans::getReagentsInternal()
{
	return
	{
		{ Silver::create(), 6 },
		{ Jade::create(), 4 },
		{ Sulfur::create(), 1 },
	};
}

Item* TaserRodPlans::clone()
{
	return TaserRodPlans::create();
}

std::string TaserRodPlans::getItemName()
{
	return TaserRodPlans::SaveKeyTaserRodPlans;
}

LocalizedString* TaserRodPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_TaserRod::create();
}

std::string TaserRodPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string TaserRodPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_TaserRod;
}

std::string TaserRodPlans::getSerializationKey()
{
	return TaserRodPlans::SaveKeyTaserRodPlans;
}
