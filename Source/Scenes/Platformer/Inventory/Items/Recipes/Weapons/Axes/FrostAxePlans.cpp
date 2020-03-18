#include "FrostAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FrostAxePlans::SaveKeyFrostAxePlans = "frost-axe-plans";

FrostAxePlans* FrostAxePlans::create()
{
	FrostAxePlans* instance = new FrostAxePlans();

	instance->autorelease();

	return instance;
}

FrostAxePlans::FrostAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

FrostAxePlans::~FrostAxePlans()
{
}

Item* FrostAxePlans::craft()
{
	return FrostAxe::create();
}

std::vector<std::tuple<Item*, int>> FrostAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* FrostAxePlans::clone()
{
	return FrostAxePlans::create();
}

std::string FrostAxePlans::getItemName()
{
	return FrostAxePlans::SaveKeyFrostAxePlans;
}

LocalizedString* FrostAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_FrostAxe::create();
}

std::string FrostAxePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string FrostAxePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_FrostAxe;
}

std::string FrostAxePlans::getSerializationKey()
{
	return FrostAxePlans::SaveKeyFrostAxePlans;
}
