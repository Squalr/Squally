#include "OldShoePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OldShoePlans::SaveKey = "old-shoe-plans";

OldShoePlans* OldShoePlans::create()
{
	OldShoePlans* instance = new OldShoePlans();

	instance->autorelease();

	return instance;
}

OldShoePlans::OldShoePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

OldShoePlans::~OldShoePlans()
{
}

std::vector<Item*> OldShoePlans::craft()
{
	return { OldShoe::create() };
}

std::vector<std::tuple<Item*, int>> OldShoePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* OldShoePlans::clone()
{
	return OldShoePlans::create();
}

LocalizedString* OldShoePlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_OldShoe::create();
}

const std::string& OldShoePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string OldShoePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_OldShoe;
}

const std::string& OldShoePlans::getIdentifier()
{
	return OldShoePlans::SaveKey;
}
