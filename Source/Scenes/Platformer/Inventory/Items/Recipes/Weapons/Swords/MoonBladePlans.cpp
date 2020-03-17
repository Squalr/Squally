#include "MoonBladePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MoonBladePlans::SaveKeyMoonBladePlans = "moon-blade-plans";

MoonBladePlans* MoonBladePlans::create()
{
	MoonBladePlans* instance = new MoonBladePlans();

	instance->autorelease();

	return instance;
}

MoonBladePlans::MoonBladePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

MoonBladePlans::~MoonBladePlans()
{
}

Item* MoonBladePlans::craft()
{
	return MoonBlade::create();
}

std::vector<std::tuple<Item*, int>> MoonBladePlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 8 },
		{ Coal::create(), 4 },
		{ Gold::create(), 2 },
		{ Emerald::create(), 1 },
	};
}

Item* MoonBladePlans::clone()
{
	return MoonBladePlans::create();
}

std::string MoonBladePlans::getItemName()
{
	return MoonBladePlans::SaveKeyMoonBladePlans;
}

LocalizedString* MoonBladePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_MoonBlade::create();
}

std::string MoonBladePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MoonBladePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_MoonBlade;
}

std::string MoonBladePlans::getSerializationKey()
{
	return MoonBladePlans::SaveKeyMoonBladePlans;
}
