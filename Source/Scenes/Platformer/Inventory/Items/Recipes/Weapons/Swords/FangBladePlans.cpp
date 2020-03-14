#include "FangBladePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FangBladePlans::SaveKeyFangBladePlans = "fang-blade-plans";

FangBladePlans* FangBladePlans::create()
{
	FangBladePlans* instance = new FangBladePlans();

	instance->autorelease();

	return instance;
}

FangBladePlans::FangBladePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

FangBladePlans::~FangBladePlans()
{
}

Item* FangBladePlans::craft()
{
	return FangBlade::create();
}

std::vector<std::tuple<Item*, int>> FangBladePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* FangBladePlans::clone()
{
	return FangBladePlans::create();
}

std::string FangBladePlans::getItemName()
{
	return FangBladePlans::SaveKeyFangBladePlans;
}

LocalizedString* FangBladePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_FangBlade::create();
}

std::string FangBladePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string FangBladePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_FangBlade;
}

std::string FangBladePlans::getSerializationKey()
{
	return FangBladePlans::SaveKeyFangBladePlans;
}
