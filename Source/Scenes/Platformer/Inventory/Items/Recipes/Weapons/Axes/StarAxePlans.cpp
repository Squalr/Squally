#include "StarAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string StarAxePlans::SaveKeyStarAxePlans = "star-axe-plans";

StarAxePlans* StarAxePlans::create()
{
	StarAxePlans* instance = new StarAxePlans();

	instance->autorelease();

	return instance;
}

StarAxePlans::StarAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

StarAxePlans::~StarAxePlans()
{
}

Item* StarAxePlans::craft()
{
	return StarAxe::create();
}

std::map<Item*, int> StarAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* StarAxePlans::clone()
{
	return StarAxePlans::create();
}

std::string StarAxePlans::getItemName()
{
	return StarAxePlans::SaveKeyStarAxePlans;
}

LocalizedString* StarAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_StarAxe::create();
}

std::string StarAxePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string StarAxePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_StarAxe;
}

std::string StarAxePlans::getSerializationKey()
{
	return StarAxePlans::SaveKeyStarAxePlans;
}
