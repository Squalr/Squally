#include "SmithingPoolTier4.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

SmithingPoolTier4* SmithingPoolTier4::create(SampleMethod sampleMethod, int min, int max)
{
	SmithingPoolTier4* instance = new SmithingPoolTier4(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

SmithingPoolTier4::SmithingPoolTier4(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "smithing-pool-t4", sampleMethod, min, max)
{
	/**************
	 Misc
	**************/
	this->addItemToPool(ItemChance::create(DarkWood::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Reasonable));

	/**************
	 Metals
	**************/
	this->addItemToPool(ItemChance::create(Mithril::create(), ItemChance::Probability::Reasonable)); // Upped drop rate based on play-testing

	// Phasing out
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Epic));

	/**************
	 Gems
	**************/
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Rare));

	// Phasing out
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Legendary));
	this->addItemToPool(ItemChance::create(Silver::create(), ItemChance::Probability::Artifact));
}

SmithingPoolTier4::~SmithingPoolTier4()
{
}
