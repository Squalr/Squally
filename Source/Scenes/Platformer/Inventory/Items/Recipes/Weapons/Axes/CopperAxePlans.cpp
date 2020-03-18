#include "CopperAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperAxePlans::SaveKeyCopperAxePlans = "copper-axe-plans";

CopperAxePlans* CopperAxePlans::create()
{
	CopperAxePlans* instance = new CopperAxePlans();

	instance->autorelease();

	return instance;
}

CopperAxePlans::CopperAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CopperAxePlans::~CopperAxePlans()
{
}

Item* CopperAxePlans::craft()
{
	return CopperAxe::create();
}

std::vector<std::tuple<Item*, int>> CopperAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* CopperAxePlans::clone()
{
	return CopperAxePlans::create();
}

std::string CopperAxePlans::getItemName()
{
	return CopperAxePlans::SaveKeyCopperAxePlans;
}

LocalizedString* CopperAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_CopperAxe::create();
}

std::string CopperAxePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string CopperAxePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_CopperAxe;
}

std::string CopperAxePlans::getSerializationKey()
{
	return CopperAxePlans::SaveKeyCopperAxePlans;
}
