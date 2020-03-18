#include "GoldenAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenAxePlans::SaveKeyGoldenAxePlans = "golden-axe-plans";

GoldenAxePlans* GoldenAxePlans::create()
{
	GoldenAxePlans* instance = new GoldenAxePlans();

	instance->autorelease();

	return instance;
}

GoldenAxePlans::GoldenAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GoldenAxePlans::~GoldenAxePlans()
{
}

Item* GoldenAxePlans::craft()
{
	return HeadSplitter::create();
}

std::vector<std::tuple<Item*, int>> GoldenAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* GoldenAxePlans::clone()
{
	return GoldenAxePlans::create();
}

std::string GoldenAxePlans::getItemName()
{
	return GoldenAxePlans::SaveKeyGoldenAxePlans;
}

LocalizedString* GoldenAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_HeadSplitter::create();
}

std::string GoldenAxePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GoldenAxePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_HeadSplitter;
}

std::string GoldenAxePlans::getSerializationKey()
{
	return GoldenAxePlans::SaveKeyGoldenAxePlans;
}
