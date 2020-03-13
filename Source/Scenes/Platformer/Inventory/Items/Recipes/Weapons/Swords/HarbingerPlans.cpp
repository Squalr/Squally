#include "HarbingerPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HarbingerPlans::SaveKeyHarbingerPlans = "harbinger-plans";

HarbingerPlans* HarbingerPlans::create()
{
	HarbingerPlans* instance = new HarbingerPlans();

	instance->autorelease();

	return instance;
}

HarbingerPlans::HarbingerPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

HarbingerPlans::~HarbingerPlans()
{
}

Item* HarbingerPlans::craft()
{
	return Harbinger::create();
}

std::map<Item*, int> HarbingerPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* HarbingerPlans::clone()
{
	return HarbingerPlans::create();
}

std::string HarbingerPlans::getItemName()
{
	return HarbingerPlans::SaveKeyHarbingerPlans;
}

LocalizedString* HarbingerPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Harbinger::create();
}

std::string HarbingerPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string HarbingerPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_Harbinger;
}

std::string HarbingerPlans::getSerializationKey()
{
	return HarbingerPlans::SaveKeyHarbingerPlans;
}
