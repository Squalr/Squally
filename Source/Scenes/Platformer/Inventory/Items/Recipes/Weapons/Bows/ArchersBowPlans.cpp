#include "ArchersBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ArchersBowPlans::SaveKeyArchersBowPlans = "archers-bow-plans";

ArchersBowPlans* ArchersBowPlans::create()
{
	ArchersBowPlans* instance = new ArchersBowPlans();

	instance->autorelease();

	return instance;
}

ArchersBowPlans::ArchersBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

ArchersBowPlans::~ArchersBowPlans()
{
}

Item* ArchersBowPlans::craft()
{
	return ArchersBow::create();
}

std::vector<std::tuple<Item*, int>> ArchersBowPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 12 },
		{ Iron::create(), 2 },
	};
}

Item* ArchersBowPlans::clone()
{
	return ArchersBowPlans::create();
}

std::string ArchersBowPlans::getItemName()
{
	return ArchersBowPlans::SaveKeyArchersBowPlans;
}

LocalizedString* ArchersBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_ArchersBow::create();
}

std::string ArchersBowPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string ArchersBowPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_ArchersBow;
}

std::string ArchersBowPlans::getSerializationKey()
{
	return ArchersBowPlans::SaveKeyArchersBowPlans;
}
