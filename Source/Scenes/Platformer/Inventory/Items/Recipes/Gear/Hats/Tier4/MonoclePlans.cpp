#include "MonoclePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MonoclePlans::SaveKey = "monocle-plans";

MonoclePlans* MonoclePlans::create()
{
	MonoclePlans* instance = new MonoclePlans();

	instance->autorelease();

	return instance;
}

MonoclePlans::MonoclePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

MonoclePlans::~MonoclePlans()
{
}

std::vector<Item*> MonoclePlans::craft()
{
	return { Monocle::create() };
}

std::vector<std::tuple<Item*, int>> MonoclePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* MonoclePlans::clone()
{
	return MonoclePlans::create();
}

LocalizedString* MonoclePlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_Monocle::create();
}

const std::string& MonoclePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MonoclePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Monocle;
}

const std::string& MonoclePlans::getIdentifier()
{
	return MonoclePlans::SaveKey;
}
