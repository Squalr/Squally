#include "IronMacePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IronMacePlans::SaveKeyIronMacePlans = "iron-mace-plans";

IronMacePlans* IronMacePlans::create()
{
	IronMacePlans* instance = new IronMacePlans();

	instance->autorelease();

	return instance;
}

IronMacePlans::IronMacePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

IronMacePlans::~IronMacePlans()
{
}

Item* IronMacePlans::craft()
{
	return IronMace::create();
}

std::vector<std::tuple<Item*, int>> IronMacePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 10 },
		{ Coal::create(), 4 },
	};
}

Item* IronMacePlans::clone()
{
	return IronMacePlans::create();
}

std::string IronMacePlans::getItemName()
{
	return IronMacePlans::SaveKeyIronMacePlans;
}

LocalizedString* IronMacePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_IronMace::create();
}

std::string IronMacePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string IronMacePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_IronMace;
}

std::string IronMacePlans::getSerializationKey()
{
	return IronMacePlans::SaveKeyIronMacePlans;
}
