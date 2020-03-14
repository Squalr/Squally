#include "FlailPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FlailPlans::SaveKeyFlailPlans = "flail-plans";

FlailPlans* FlailPlans::create()
{
	FlailPlans* instance = new FlailPlans();

	instance->autorelease();

	return instance;
}

FlailPlans::FlailPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

FlailPlans::~FlailPlans()
{
}

Item* FlailPlans::craft()
{
	return Flail::create();
}

std::vector<std::tuple<Item*, int>> FlailPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 10 },
		{ Coal::create(), 4 },
	};
}

Item* FlailPlans::clone()
{
	return FlailPlans::create();
}

std::string FlailPlans::getItemName()
{
	return FlailPlans::SaveKeyFlailPlans;
}

LocalizedString* FlailPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_Flail::create();
}

std::string FlailPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string FlailPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_Flail;
}

std::string FlailPlans::getSerializationKey()
{
	return FlailPlans::SaveKeyFlailPlans;
}
