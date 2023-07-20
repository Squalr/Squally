#include "SmithingPoolTier5.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

SmithingPoolTier5* SmithingPoolTier5::create(SampleMethod sampleMethod, int min, int max)
{
	SmithingPoolTier5* instance = new SmithingPoolTier5(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

SmithingPoolTier5::SmithingPoolTier5(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "smithing-pool-t5", sampleMethod, min, max)
{
	/**************
	 Misc
	**************/
	this->addItemToPool(ItemChance::create(DarkWood::create(), ItemChance::Probability::Uncommon)); // Lowered rate due to limited uses
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Reasonable));

	/**************
	 Metals
	**************/
	// Higher drop rate than normal, with two separate rolls, since 2x more are required for crafts
	this->addItemToPool(ItemChance::create(Bone::create(), ItemChance::Probability::Reasonable));
	this->addItemToPool(ItemChance::create(Bone::create(), ItemChance::Probability::Reasonable));

	// Phasing out
	this->addItemToPool(ItemChance::create(Mithril::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Epic));

	/**************
	 Gems
	**************/
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Rare));

	// Phasing out
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Legendary));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Artifact));
}

SmithingPoolTier5::~SmithingPoolTier5()
{
}
