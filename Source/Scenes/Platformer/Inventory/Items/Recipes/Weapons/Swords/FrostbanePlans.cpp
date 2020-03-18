#include "FrostbanePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FrostbanePlans::SaveKeyFrostbanePlans = "frost-bane-plans";

FrostbanePlans* FrostbanePlans::create()
{
	FrostbanePlans* instance = new FrostbanePlans();

	instance->autorelease();

	return instance;
}

FrostbanePlans::FrostbanePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

FrostbanePlans::~FrostbanePlans()
{
}

Item* FrostbanePlans::craft()
{
	return Frostbane::create();
}

std::vector<std::tuple<Item*, int>> FrostbanePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 1 },
		{ Iron::create(), 8 },
		{ Coal::create(), 2 },
	};
}

Item* FrostbanePlans::clone()
{
	return FrostbanePlans::create();
}

std::string FrostbanePlans::getItemName()
{
	return FrostbanePlans::SaveKeyFrostbanePlans;
}

LocalizedString* FrostbanePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Frostbane::create();
}

std::string FrostbanePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string FrostbanePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_Frostbane;
}

std::string FrostbanePlans::getSerializationKey()
{
	return FrostbanePlans::SaveKeyFrostbanePlans;
}
