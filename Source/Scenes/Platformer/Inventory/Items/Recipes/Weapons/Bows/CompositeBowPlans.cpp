#include "CompositeBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CompositeBowPlans::SaveKeyCompositeBowPlans = "composite-bow-plans";

CompositeBowPlans* CompositeBowPlans::create()
{
	CompositeBowPlans* instance = new CompositeBowPlans();

	instance->autorelease();

	return instance;
}

CompositeBowPlans::CompositeBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CompositeBowPlans::~CompositeBowPlans()
{
}

Item* CompositeBowPlans::craft()
{
	return CompositeBow::create();
}

std::map<Item*, int> CompositeBowPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* CompositeBowPlans::clone()
{
	return CompositeBowPlans::create();
}

std::string CompositeBowPlans::getItemName()
{
	return CompositeBowPlans::SaveKeyCompositeBowPlans;
}

LocalizedString* CompositeBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_CompositeBow::create();
}

std::string CompositeBowPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string CompositeBowPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_CompositeBow;
}

std::string CompositeBowPlans::getSerializationKey()
{
	return CompositeBowPlans::SaveKeyCompositeBowPlans;
}
