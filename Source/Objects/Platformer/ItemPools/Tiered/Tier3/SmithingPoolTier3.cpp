#include "SmithingPoolTier3.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

SmithingPoolTier3* SmithingPoolTier3::create(SampleMethod sampleMethod, int min, int max)
{
	SmithingPoolTier3* instance = new SmithingPoolTier3(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

SmithingPoolTier3::SmithingPoolTier3(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "smithing-pool-t3", sampleMethod, min, max)
{
	/**************
	 Misc
	**************/
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Reasonable));

	// Phasing out
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Uncommon));

	/**************
	 Metals
	**************/
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Uncommon));

	// Phasing out
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Epic));

	/**************
	 Gems
	**************/
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Rare));

	// Phasing out
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Legendary));
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Artifact));
}

SmithingPoolTier3::~SmithingPoolTier3()
{
}
