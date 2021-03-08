#include "VoidMacePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidMacePlans::SaveKey = "void-mace-plans";

VoidMacePlans* VoidMacePlans::create()
{
	VoidMacePlans* instance = new VoidMacePlans();

	instance->autorelease();

	return instance;
}

VoidMacePlans::VoidMacePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

VoidMacePlans::~VoidMacePlans()
{
}

std::vector<Item*> VoidMacePlans::craft()
{
	return { VoidMace::create() };
}

std::vector<std::tuple<Item*, int>> VoidMacePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 8 },
		{ Coal::create(), 8 },
	};
}

Item* VoidMacePlans::clone()
{
	return VoidMacePlans::create();
}

const std::string& VoidMacePlans::getItemName()
{
	return VoidMacePlans::SaveKey;
}

LocalizedString* VoidMacePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_VoidMace::create();
}

const std::string& VoidMacePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string VoidMacePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_VoidMace;
}

const std::string& VoidMacePlans::getIdentifier()
{
	return VoidMacePlans::SaveKey;
}
