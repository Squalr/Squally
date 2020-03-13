#include "HandAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HandAxePlans::SaveKeyHandAxePlans = "hand-axe-plans";

HandAxePlans* HandAxePlans::create()
{
	HandAxePlans* instance = new HandAxePlans();

	instance->autorelease();

	return instance;
}

HandAxePlans::HandAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

HandAxePlans::~HandAxePlans()
{
}

Item* HandAxePlans::craft()
{
	return HandAxe::create();
}

std::map<Item*, int> HandAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* HandAxePlans::clone()
{
	return HandAxePlans::create();
}

std::string HandAxePlans::getItemName()
{
	return HandAxePlans::SaveKeyHandAxePlans;
}

LocalizedString* HandAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_HandAxe::create();
}

std::string HandAxePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string HandAxePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_HandAxe;
}

std::string HandAxePlans::getSerializationKey()
{
	return HandAxePlans::SaveKeyHandAxePlans;
}
