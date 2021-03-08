#include "MithrilMacePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilMacePlans::SaveKey = "mithril-mace-plans";

MithrilMacePlans* MithrilMacePlans::create()
{
	MithrilMacePlans* instance = new MithrilMacePlans();

	instance->autorelease();

	return instance;
}

MithrilMacePlans::MithrilMacePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

MithrilMacePlans::~MithrilMacePlans()
{
}

std::vector<Item*> MithrilMacePlans::craft()
{
	return { MithrilMace::create() };
}

std::vector<std::tuple<Item*, int>> MithrilMacePlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 2 },
		{ Mithril::create(), 6 },
		{ Coal::create(), 4 },
	};
}

Item* MithrilMacePlans::clone()
{
	return MithrilMacePlans::create();
}

const std::string& MithrilMacePlans::getItemName()
{
	return MithrilMacePlans::SaveKey;
}

LocalizedString* MithrilMacePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_MithrilMace::create();
}

const std::string& MithrilMacePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MithrilMacePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_MithrilMace;
}

const std::string& MithrilMacePlans::getSerializationKey()
{
	return MithrilMacePlans::SaveKey;
}
