#include "GoldenAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenAxePlans::SaveKey = "golden-axe-plans";

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

std::vector<Item*> GoldenAxePlans::craft()
{
	return { GoldenAxe::create() };
}

std::vector<std::tuple<Item*, int>> GoldenAxePlans::getReagentsInternal()
{
	return
	{
		{ Gold::create(), 5 },
		{ Iron::create(), 4 },
		{ Coal::create(), 5 },
	};
}

Item* GoldenAxePlans::clone()
{
	return GoldenAxePlans::create();
}

const std::string& GoldenAxePlans::getItemName()
{
	return GoldenAxePlans::SaveKey;
}

LocalizedString* GoldenAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_GoldenAxe::create();
}

const std::string& GoldenAxePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GoldenAxePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_GoldenAxe;
}

const std::string& GoldenAxePlans::getIdentifier()
{
	return GoldenAxePlans::SaveKey;
}
