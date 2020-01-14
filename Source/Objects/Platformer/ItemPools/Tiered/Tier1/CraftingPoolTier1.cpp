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
	// Gems
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Legendary));

	// Metals
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Silver::create(), ItemChance::Probability::Epic));

	// Materials
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Dirt::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Stone::create(), ItemChance::Probability::Common));
}

CraftingPoolTier1::~CraftingPoolTier1()
{
}
