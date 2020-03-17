#include "GladiusPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GladiusPlans::SaveKeyGladiusPlans = "gladius-plans";

GladiusPlans* GladiusPlans::create()
{
	GladiusPlans* instance = new GladiusPlans();

	instance->autorelease();

	return instance;
}

GladiusPlans::GladiusPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GladiusPlans::~GladiusPlans()
{
}

Item* GladiusPlans::craft()
{
	return Gladius::create();
}

std::vector<std::tuple<Item*, int>> GladiusPlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 8 },
		{ Coal::create(), 4 },
		{ Gold::create(), 2 },
	};
}

Item* GladiusPlans::clone()
{
	return GladiusPlans::create();
}

std::string GladiusPlans::getItemName()
{
	return GladiusPlans::SaveKeyGladiusPlans;
}

LocalizedString* GladiusPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Gladius::create();
}

std::string GladiusPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GladiusPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_Gladius;
}

std::string GladiusPlans::getSerializationKey()
{
	return GladiusPlans::SaveKeyGladiusPlans;
}
