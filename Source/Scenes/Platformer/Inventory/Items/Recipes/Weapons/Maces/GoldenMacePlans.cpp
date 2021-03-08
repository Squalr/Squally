#include "GoldenMacePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenMacePlans::SaveKey = "golden-mace-plans";

GoldenMacePlans* GoldenMacePlans::create()
{
	GoldenMacePlans* instance = new GoldenMacePlans();

	instance->autorelease();

	return instance;
}

GoldenMacePlans::GoldenMacePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GoldenMacePlans::~GoldenMacePlans()
{
}

std::vector<Item*> GoldenMacePlans::craft()
{
	return { GoldenMace::create() };
}

std::vector<std::tuple<Item*, int>> GoldenMacePlans::getReagentsInternal()
{
	return
	{
		{ Gold::create(), 6 },
		{ Iron::create(), 4 },
		{ Coal::create(), 6 },
	};
}

Item* GoldenMacePlans::clone()
{
	return GoldenMacePlans::create();
}

const std::string& GoldenMacePlans::getItemName()
{
	return GoldenMacePlans::SaveKey;
}

LocalizedString* GoldenMacePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_GoldenMace::create();
}

const std::string& GoldenMacePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GoldenMacePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_GoldenMace;
}

const std::string& GoldenMacePlans::getIdentifier()
{
	return GoldenMacePlans::SaveKey;
}
