#include "IronAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IronAxePlans::SaveKeyIronAxePlans = "iron-axe-plans";

IronAxePlans* IronAxePlans::create()
{
	IronAxePlans* instance = new IronAxePlans();

	instance->autorelease();

	return instance;
}

IronAxePlans::IronAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

IronAxePlans::~IronAxePlans()
{
}

Item* IronAxePlans::craft()
{
	return IronAxe::create();
}

std::map<Item*, int> IronAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* IronAxePlans::clone()
{
	return IronAxePlans::create();
}

std::string IronAxePlans::getItemName()
{
	return IronAxePlans::SaveKeyIronAxePlans;
}

LocalizedString* IronAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_IronAxe::create();
}

std::string IronAxePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string IronAxePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_IronAxe;
}

std::string IronAxePlans::getSerializationKey()
{
	return IronAxePlans::SaveKeyIronAxePlans;
}
