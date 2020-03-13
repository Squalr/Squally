#include "ImpalerPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ImpalerPlans::SaveKeyImpalerPlans = "impaler-plans";

ImpalerPlans* ImpalerPlans::create()
{
	ImpalerPlans* instance = new ImpalerPlans();

	instance->autorelease();

	return instance;
}

ImpalerPlans::ImpalerPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

ImpalerPlans::~ImpalerPlans()
{
}

Item* ImpalerPlans::craft()
{
	return CompositeBow::create();
}

std::map<Item*, int> ImpalerPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* ImpalerPlans::clone()
{
	return ImpalerPlans::create();
}

std::string ImpalerPlans::getItemName()
{
	return ImpalerPlans::SaveKeyImpalerPlans;
}

LocalizedString* ImpalerPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Spears_Impaler::create();
}

std::string ImpalerPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string ImpalerPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Spears_Impaler;
}

std::string ImpalerPlans::getSerializationKey()
{
	return ImpalerPlans::SaveKeyImpalerPlans;
}
