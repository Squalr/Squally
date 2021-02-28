#include "BoneHammerPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneHammerPlans::SaveKey = "bone-hammer-plans";

BoneHammerPlans* BoneHammerPlans::create()
{
	BoneHammerPlans* instance = new BoneHammerPlans();

	instance->autorelease();

	return instance;
}

BoneHammerPlans::BoneHammerPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BoneHammerPlans::~BoneHammerPlans()
{
}

std::vector<Item*> BoneHammerPlans::craft()
{
	return { BoneHammer::create() };
}

std::vector<std::tuple<Item*, int>> BoneHammerPlans::getReagentsInternal()
{
	return
	{
		{ DarkWood::create(), 2 },
		{ Obsidian::create(), 2 },
	};
}

Item* BoneHammerPlans::clone()
{
	return BoneHammerPlans::create();
}

std::string BoneHammerPlans::getItemName()
{
	return BoneHammerPlans::SaveKey;
}

LocalizedString* BoneHammerPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_BoneHammer::create();
}

std::string BoneHammerPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string BoneHammerPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_BoneHammer;
}

std::string BoneHammerPlans::getSerializationKey()
{
	return BoneHammerPlans::SaveKey;
}
