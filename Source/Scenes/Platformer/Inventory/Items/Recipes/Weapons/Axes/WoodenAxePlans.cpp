#include "WoodenAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenAxePlans::SaveKey = "wooden-axe-plans";

WoodenAxePlans* WoodenAxePlans::create()
{
	WoodenAxePlans* instance = new WoodenAxePlans();

	instance->autorelease();

	return instance;
}

WoodenAxePlans::WoodenAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WoodenAxePlans::~WoodenAxePlans()
{
}

Item* WoodenAxePlans::craft()
{
	return WoodenAxe::create();
}

std::vector<std::tuple<Item*, int>> WoodenAxePlans::getReagentsInternal()
{
	return
	{
		{ LightWood::create(), 8 },
		{ Iron::create(), 4 },
		{ Coal::create(), 2 },
	};
}

Item* WoodenAxePlans::clone()
{
	return WoodenAxePlans::create();
}

std::string WoodenAxePlans::getItemName()
{
	return WoodenAxePlans::SaveKey;
}

LocalizedString* WoodenAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_WoodenAxe::create();
}

std::string WoodenAxePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WoodenAxePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_WoodenAxe;
}

std::string WoodenAxePlans::getSerializationKey()
{
	return WoodenAxePlans::SaveKey;
}
