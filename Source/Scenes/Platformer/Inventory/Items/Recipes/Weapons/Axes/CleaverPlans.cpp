#include "CleaverPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CleaverPlans::SaveKeyCleaverPlans = "blue-axe-plans";

CleaverPlans* CleaverPlans::create()
{
	CleaverPlans* instance = new CleaverPlans();

	instance->autorelease();

	return instance;
}

CleaverPlans::CleaverPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CleaverPlans::~CleaverPlans()
{
}

Item* CleaverPlans::craft()
{
	return Cleaver::create();
}

std::map<Item*, int> CleaverPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* CleaverPlans::clone()
{
	return CleaverPlans::create();
}

std::string CleaverPlans::getItemName()
{
	return CleaverPlans::SaveKeyCleaverPlans;
}

LocalizedString* CleaverPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_Cleaver::create();
}

std::string CleaverPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string CleaverPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_Cleaver;
}

std::string CleaverPlans::getSerializationKey()
{
	return CleaverPlans::SaveKeyCleaverPlans;
}
