#include "WarCutlasPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WarCutlasPlans::SaveKeyWarCutlasPlans = "war-cutlas-plans";

WarCutlasPlans* WarCutlasPlans::create()
{
	WarCutlasPlans* instance = new WarCutlasPlans();

	instance->autorelease();

	return instance;
}

WarCutlasPlans::WarCutlasPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WarCutlasPlans::~WarCutlasPlans()
{
}

Item* WarCutlasPlans::craft()
{
	return WarCutlas::create();
}

std::vector<std::tuple<Item*, int>> WarCutlasPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 1 },
		{ Iron::create(), 10 },
	};
}

Item* WarCutlasPlans::clone()
{
	return WarCutlasPlans::create();
}

std::string WarCutlasPlans::getItemName()
{
	return WarCutlasPlans::SaveKeyWarCutlasPlans;
}

LocalizedString* WarCutlasPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_WarCutlas::create();
}

std::string WarCutlasPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WarCutlasPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_WarCutlas;
}

std::string WarCutlasPlans::getSerializationKey()
{
	return WarCutlasPlans::SaveKeyWarCutlasPlans;
}
