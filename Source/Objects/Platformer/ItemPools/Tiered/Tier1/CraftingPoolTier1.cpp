#include "CraftingPoolTier1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

CraftingPoolTier1* CraftingPoolTier1::create(SampleMethod sampleMethod, int min, int max)
{
	CraftingPoolTier1* instance = new CraftingPoolTier1(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

CraftingPoolTier1::CraftingPoolTier1(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "crafting-pool-t1", sampleMethod, min, max)
{
	// Alchemy
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Reasonable));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Reasonable));

	// Smithing
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Reasonable));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Tin::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Rare));
}

CraftingPoolTier1::~CraftingPoolTier1()
{
}
