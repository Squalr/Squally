#include "SmithingPoolTier7.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

SmithingPoolTier7* SmithingPoolTier7::create(SampleMethod sampleMethod, int min, int max)
{
	SmithingPoolTier7* instance = new SmithingPoolTier7(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

SmithingPoolTier7::SmithingPoolTier7(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "smithing-pool-t7", sampleMethod, min, max)
{
	/**************
	 Misc
	**************/
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Reasonable));

	// Phasing out
	this->addItemToPool(ItemChance::create(DarkWood::create(), ItemChance::Probability::Uncommon));

	/**************
	 Metals
	**************/
	this->addItemToPool(ItemChance::create(Crystal::create(), ItemChance::Probability::Uncommon));

	/**************
	 Gems
	**************/
	// Phasing out
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Legendary));
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Artifact));
}

SmithingPoolTier7::~SmithingPoolTier7()
{
}
