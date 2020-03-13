#include "WoodenMalletPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenMalletPlans::SaveKeyWoodenMalletPlans = "wooden-mallet-plans";

WoodenMalletPlans* WoodenMalletPlans::create()
{
	WoodenMalletPlans* instance = new WoodenMalletPlans();

	instance->autorelease();

	return instance;
}

WoodenMalletPlans::WoodenMalletPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WoodenMalletPlans::~WoodenMalletPlans()
{
}

Item* WoodenMalletPlans::craft()
{
	return WoodenMallet::create();
}

std::map<Item*, int> WoodenMalletPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WoodenMalletPlans::clone()
{
	return WoodenMalletPlans::create();
}

std::string WoodenMalletPlans::getItemName()
{
	return WoodenMalletPlans::SaveKeyWoodenMalletPlans;
}

LocalizedString* WoodenMalletPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_WoodenMallet::create();
}

std::string WoodenMalletPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string WoodenMalletPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_WoodenMallet;
}

std::string WoodenMalletPlans::getSerializationKey()
{
	return WoodenMalletPlans::SaveKeyWoodenMalletPlans;
}
