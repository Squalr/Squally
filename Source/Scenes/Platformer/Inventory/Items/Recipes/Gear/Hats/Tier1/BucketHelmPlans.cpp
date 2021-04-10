#include "BucketHelmPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BucketHelmPlans::SaveKey = "bucket-helm-plans";

BucketHelmPlans* BucketHelmPlans::create()
{
	BucketHelmPlans* instance = new BucketHelmPlans();

	instance->autorelease();

	return instance;
}

BucketHelmPlans::BucketHelmPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BucketHelmPlans::~BucketHelmPlans()
{
}

std::vector<Item*> BucketHelmPlans::craft()
{
	return { BucketHelm::create() };
}

std::vector<std::tuple<Item*, int>> BucketHelmPlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 5 },
	};
}

Item* BucketHelmPlans::clone()
{
	return BucketHelmPlans::create();
}

LocalizedString* BucketHelmPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_BucketHelm::create();
}

const std::string& BucketHelmPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string BucketHelmPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_BucketHelm;
}

const std::string& BucketHelmPlans::getIdentifier()
{
	return BucketHelmPlans::SaveKey;
}
