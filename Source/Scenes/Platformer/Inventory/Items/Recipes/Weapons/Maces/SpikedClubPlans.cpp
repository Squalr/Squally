#include "SpikedClubPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpikedClubPlans::SaveKeySpikedClubPlans = "spiked-club-plans";

SpikedClubPlans* SpikedClubPlans::create()
{
	SpikedClubPlans* instance = new SpikedClubPlans();

	instance->autorelease();

	return instance;
}

SpikedClubPlans::SpikedClubPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SpikedClubPlans::~SpikedClubPlans()
{
}

Item* SpikedClubPlans::craft()
{
	return SpikedClub::create();
}

std::vector<std::tuple<Item*, int>> SpikedClubPlans::getReagentsInternal()
{
	return
	{
		{ Copper::create(), 3 },
		{ LightWood::create(), 10 },
		{ Iron::create(), 2 },
	};
}

Item* SpikedClubPlans::clone()
{
	return SpikedClubPlans::create();
}

std::string SpikedClubPlans::getItemName()
{
	return SpikedClubPlans::SaveKeySpikedClubPlans;
}

LocalizedString* SpikedClubPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_SpikedClub::create();
}

std::string SpikedClubPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string SpikedClubPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_SpikedClub;
}

std::string SpikedClubPlans::getSerializationKey()
{
	return SpikedClubPlans::SaveKeySpikedClubPlans;
}
