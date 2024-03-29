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
		{ Bone::create(), 16 },
		{ Iron::create(), 4 },
		{ DarkWood::create(), 2 },
	};
}

Item* BoneHammerPlans::clone()
{
	return BoneHammerPlans::create();
}

LocalizedString* BoneHammerPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_BoneHammer::create();
}

const std::string& BoneHammerPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string BoneHammerPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_BoneHammer;
}

const std::string& BoneHammerPlans::getIdentifier()
{
	return BoneHammerPlans::SaveKey;
}
