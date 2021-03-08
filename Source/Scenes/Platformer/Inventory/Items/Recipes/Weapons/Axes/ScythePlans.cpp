#include "ScythePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ScythePlans::SaveKey = "scythe-plans";

ScythePlans* ScythePlans::create()
{
	ScythePlans* instance = new ScythePlans();

	instance->autorelease();

	return instance;
}

ScythePlans::ScythePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

ScythePlans::~ScythePlans()
{
}

std::vector<Item*> ScythePlans::craft()
{
	return { Scythe::create() };
}

std::vector<std::tuple<Item*, int>> ScythePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* ScythePlans::clone()
{
	return ScythePlans::create();
}

const std::string& ScythePlans::getItemName()
{
	return ScythePlans::SaveKey;
}

LocalizedString* ScythePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_Scythe::create();
}

const std::string& ScythePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string ScythePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Special_Scythe;
}

const std::string& ScythePlans::getSerializationKey()
{
	return ScythePlans::SaveKey;
}
